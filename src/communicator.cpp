#include "../inc/communicator.h"
#include <stdio.h>
#include <unistd.h>

using namespace std;

communicator::communicator(uint32_t process_id, unsigned int number_of_processes) {
	this->process_id = process_id;
	this->number_of_processes = number_of_processes;
	time = 0;
	enabled = true;
}

void communicator::send_lock_request(uint16_t critical_section_id, pthread_mutex_t* waiting_process_mutex) {
	printf("Process: %d, Time: %d, Trying to enter section %d\n", process_id, time, critical_section_id);
	pthread_mutex_lock(&internal_state_mutex);

	lock_request request(process_id, time, critical_section_id);
	requests_descriptors[request] = request_descriptor(waiting_process_mutex, 1);

	lock_requests[critical_section_id].insert(request);
	own_requests[critical_section_id] = &*lock_requests[critical_section_id].find(request);

	++time;
	frame message(time, MESSAGE_TAG::LOCK_REQUEST, &request);
	broadcast_message(&message);

	pthread_mutex_unlock(&internal_state_mutex);
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
	printf("Process: %d, Time: %d, Lock request arrived: (from: %d, created at:%d, for section:%d)\n", process_id, time, request->process_id, request->creation_time, request->critical_section_id);

	lock_requests[request->critical_section_id].insert(*request);

	const lock_request* answer = (own_requests.find(request->critical_section_id) == own_requests.end()) ? request : own_requests[request->critical_section_id];

	lock_response response(request, answer);

	++time;
	frame message(time, MESSAGE_TAG::LOCK_RESPONSE, &response);
	send_message(&message, request->process_id);

	delete request;
}

void communicator::handle(lock_response* response) {
	printf("Process: %d, Time: %d, Lock response arrived, answer(process: %d, created_at: %d, for section: %d)\n", process_id, time, response->answer.process_id,
		response->answer.creation_time, response->answer.critical_section_id);

	++(&requests_descriptors[response->confirmed_request])->number_of_confirmations;
	lock_requests[response->answer.critical_section_id].insert(response->answer);

	try_to_enter(response->answer.critical_section_id);

	delete response;
}

void communicator::try_to_enter(uint16_t critical_section_id) {
	map<uint16_t, const lock_request*>::iterator own_requests_iterator = own_requests.find(critical_section_id);
	if(own_requests_iterator != own_requests.end()) {
		const lock_request* own_request = own_requests_iterator->second;
		request_descriptor* descriptor = &requests_descriptors[*own_request];

		if(descriptor->number_of_confirmations == number_of_processes && *lock_requests[critical_section_id].begin() == *own_request) {
			printf("Process: %d, time: %d, entering section %d\n", process_id, time, critical_section_id);
			pthread_mutex_unlock(descriptor->mutex);
		}
	}
}

void communicator::handle(release_signal* signal) {
	lock_request* released_request = &signal->released_request;

	printf("Process: %d, Time: %d, Somebody released section %d\n", process_id, time, released_request->critical_section_id);

	lock_requests[released_request->critical_section_id].erase(*released_request);

	try_to_enter(released_request->critical_section_id);

	delete signal;
}

void communicator::handle(wait_signal* signal) {
/*
	lock_request* request_to_remove = &signal->request_to_remove;

	printf("Process: %d, Time: %d, Received wait signal from %d\n", process_id, time, request_to_remove->process_id);

	lock_requests
*/
	delete signal;
}

void communicator::send_release_signal(uint16_t critical_section_id) {
	pthread_mutex_lock(&internal_state_mutex);
	const lock_request* request_to_release = own_requests[critical_section_id];

	printf("Process: %d, Time: %d, Leaving section %d\n", process_id, time, request_to_release->critical_section_id);

	++time;
	release_signal request_release_signal(request_to_release);
	frame message(time, MESSAGE_TAG::RELEASE_SIGNAL, &request_release_signal);
	broadcast_message(&message);

	requests_descriptors.erase(*request_to_release);
	own_requests.erase(critical_section_id);
	lock_requests[critical_section_id].erase(*request_to_release);

	pthread_mutex_unlock(&internal_state_mutex);
}

void communicator::send_wait_signal(uint16_t critical_section_id, pthread_mutex_t* mutex) {
	pthread_mutex_lock(&internal_state_mutex);

	++time;
	printf("Process: %d, Time: %d, Waiting in section %d\n", process_id, time, critical_section_id);

	const lock_request* request_to_remove = own_requests[critical_section_id];
	wait_signal signal(request_to_remove);
		
	wait_signals[critical_section_id].insert(signal);

	pthread_mutex_unlock(&internal_state_mutex);
}

void communicator::send_wake_signal(uint16_t critical_section_id) {
	pthread_mutex_lock(&internal_state_mutex);
	++time;
	pthread_mutex_unlock(&internal_state_mutex);
}

communicator::~communicator() {
	pthread_mutex_destroy(&internal_state_mutex);	
}
