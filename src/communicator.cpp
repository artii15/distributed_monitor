#include "../inc/communicator.h"

using namespace std;

communicator::communicator(uint32_t process_id, unsigned int number_of_processes) {
	this->process_id = process_id;
	this->number_of_processes = number_of_processes;
	time = 0;
	enabled = true;
}

lock_request communicator::send_lock_request(uint16_t critical_section_id, pthread_mutex_t* waiting_process_mutex) {
	pthread_mutex_lock(&internal_state_mutex);
	lock_request request(process_id, time, critical_section_id);

	lock_requests[request.critical_section_id].insert(request);
	requests_descriptors[request] = request_descriptor(waiting_process_mutex, 1);

	frame message(time, MESSAGE_TAG::LOCK_REQUEST, &request);
	broadcast_message(&message);

	++time;

	pthread_mutex_unlock(&internal_state_mutex);

	return request;
}

void communicator::listen() {
	while(enabled) {
		frame* message = receive_message();
		
		pthread_mutex_lock(&internal_state_mutex);

		time = ((message->time > time) ? message->time : time) + 1;
		message->payload->be_handled_by(this);
		delete message;

		pthread_mutex_unlock(&internal_state_mutex);
	}
}

void communicator::handle(lock_request* request) {
	lock_requests[request->critical_section_id].insert(*request);
	const lock_request* top_request = &*lock_requests[request->critical_section_id].begin();

	lock_response response(request, top_request);
	frame message(time, MESSAGE_TAG::LOCK_RESPONSE, &response);

	send_message(&message, request->process_id);
	++time;

	delete request;
}

void communicator::handle(lock_response* response) {
	request_descriptor* confirmed_request_descriptor = &requests_descriptors[response->confirmed_request];
	++confirmed_request_descriptor->number_of_confirmations;

	lock_requests[response->top_request.critical_section_id].insert(response->top_request);

	if(can_process_enter(&response->confirmed_request, confirmed_request_descriptor)) {
		pthread_mutex_unlock(confirmed_request_descriptor->mutex);
	}

	delete response;
}

void communicator::send_release_signal(lock_request* request_to_release) {
	pthread_mutex_lock(&internal_state_mutex);

	frame message(time, MESSAGE_TAG::RELEASE_SIGNAL, request_to_release);

	broadcast_message(&message);
	++time;

	requests_descriptors.erase(*request_to_release);
	lock_requests[request_to_release->critical_section_id].erase(*request_to_release);

	pthread_mutex_unlock(&internal_state_mutex);
}

bool communicator::can_process_enter(lock_request* request, request_descriptor* descriptor) {
	return descriptor->number_of_confirmations == number_of_processes && *lock_requests[request->critical_section_id].begin() == *request;
}

communicator::~communicator() {
	pthread_mutex_destroy(&internal_state_mutex);	
}
