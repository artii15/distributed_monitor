#include "../../inc/synchronizer/synchronizer.h"

using namespace std;

synchronizer::synchronizer(communicator* comm, const environment_descriptor* env) {
	this->comm = comm;
	this->env = env;
	this->time = 0;
}

void synchronizer::handle(uint8_t* raw_message, uint16_t tag) {
	pthread_mutex_lock(&internal_state_mutex);
	uint32_t message_time = 0;
	switch(tag) {
		case MESSAGE_TAG::LOCK_REQUEST: {
			lock_request request(raw_message);
			message_time = request.time;
			handle(&request);
			break;
		}
		case MESSAGE_TAG::LOCK_RESPONSE: {
			lock_response response(raw_message);
			message_time = response.time;
			handle(&response);
			break;
		}
		case MESSAGE_TAG::RELEASE_SIGNAL: {
			release_signal signal(raw_message);
			message_time = signal.time;
			handle(&signal);
			break;
		}
		case MESSAGE_TAG::WAIT_SIGNAL: {
			wait_signal signal(raw_message);
			message_time = signal.time;
			handle(&signal);
			break;
		}
		case MESSAGE_TAG::WAKE_SIGNAL: {
			wake_signal signal(raw_message);
			message_time = signal.time;
			handle(&signal);
			break;
		}
	}
	time = ((message_time > time) ? message_time : time) + 1;
	pthread_mutex_unlock(&internal_state_mutex);
}

void synchronizer::handle(lock_request* request) {
	lock_requests[request->critical_section_id].insert(*request);

	const lock_request* answer = (own_requests.find(request->critical_section_id) == own_requests.end()) ? request : own_requests[request->critical_section_id];
	lock_response response(MESSAGE_TAG::LOCK_RESPONSE, ++time, request, answer);

	comm->send_message(&response, request->process_id);
}

void synchronizer::handle(lock_response* response) {
	++(&requests_descriptors[response->confirmed_request])->number_of_confirmations;
	lock_requests[response->answer.critical_section_id].insert(response->answer);

	try_to_enter(response->answer.critical_section_id);
}

void synchronizer::handle(release_signal* signal) {
	lock_request* released_request = &signal->released_request;

	lock_requests[released_request->critical_section_id].erase(*released_request);

	try_to_enter(released_request->critical_section_id);
}

void synchronizer::handle(wait_signal* signal) {
	lock_request* request_to_remove = &signal->request_to_remove;
	uint16_t critical_section_id = request_to_remove->critical_section_id;

	lock_requests[critical_section_id].erase(*request_to_remove);
	wait_signals[critical_section_id].insert(*signal);

	try_to_enter(critical_section_id);
}

void synchronizer::handle(wake_signal* signal) {
	wait_signal* signal_to_release = &signal->signal_to_release;	
	uint16_t critical_section_id = signal_to_release->request_to_remove.critical_section_id;

	map<uint16_t, const wait_signal*>::iterator own_wait_signal_iterator = own_wait_signals.find(critical_section_id);

	if(own_wait_signal_iterator != own_wait_signals.end() && *signal_to_release == *own_wait_signal_iterator->second) {
		own_wait_signals.erase(critical_section_id);
		
		pthread_mutex_t* wait_signal_mutex = wait_signals_mutexes[*signal_to_release];
		wait_signals_mutexes.erase(*signal_to_release);

		request_section_lock(critical_section_id, wait_signal_mutex);
	}

	wait_signals[critical_section_id].erase(*signal_to_release);
}

void synchronizer::try_to_enter(uint16_t critical_section_id) {
	map<uint16_t, const lock_request*>::iterator own_requests_iterator = own_requests.find(critical_section_id);
	if(own_requests_iterator != own_requests.end()) {
		const lock_request* own_request = own_requests_iterator->second;
		request_descriptor* descriptor = &requests_descriptors[*own_request];

		if(descriptor->number_of_confirmations == env->number_of_processes && *lock_requests[critical_section_id].begin() == *own_request) {
			pthread_mutex_unlock(descriptor->mutex);
			requests_descriptors.erase(*own_request);
		}
	}
}

void synchronizer::lock_section(uint16_t critical_section_id, pthread_mutex_t* waiting_process_mutex) {
	pthread_mutex_lock(&internal_state_mutex);

	request_section_lock(critical_section_id, waiting_process_mutex);

	pthread_mutex_unlock(&internal_state_mutex);
}

void synchronizer::request_section_lock(uint16_t critical_section_id, pthread_mutex_t* waiting_process_mutex) {
	lock_request request(MESSAGE_TAG::LOCK_REQUEST, ++time, env->process_id, critical_section_id);
	requests_descriptors[request] = request_descriptor(waiting_process_mutex, 1);

	lock_requests[critical_section_id].insert(request);
	own_requests[critical_section_id] = &*lock_requests[critical_section_id].find(request);

	comm->broadcast_message(&request);
}

void synchronizer::release_section(uint16_t critical_section_id) {
	pthread_mutex_lock(&internal_state_mutex);

	const lock_request* request_to_release = own_requests[critical_section_id];

	release_signal request_release_signal(MESSAGE_TAG::RELEASE_SIGNAL, ++time, request_to_release);
	comm->broadcast_message(&request_release_signal);

	own_requests.erase(critical_section_id);
	lock_requests[critical_section_id].erase(*request_to_release);

	pthread_mutex_unlock(&internal_state_mutex);
}

void synchronizer::wake_all_in_section(uint16_t critical_section_id) {
	pthread_mutex_lock(&internal_state_mutex);

	while(!wait_signals[critical_section_id].empty()) {
		notify_one_process(critical_section_id);
	}

	pthread_mutex_unlock(&internal_state_mutex);
}

void synchronizer::wake_one_in_section(uint16_t critical_section_id) {
	pthread_mutex_lock(&internal_state_mutex);

	if(!wait_signals[critical_section_id].empty()) {
		notify_one_process(critical_section_id);
	}

	pthread_mutex_unlock(&internal_state_mutex);
}

void synchronizer::notify_one_process(uint16_t critical_section_id) {
	const wait_signal* signal_to_remove = &*wait_signals[critical_section_id].begin();
	wake_signal	signal(MESSAGE_TAG::WAKE_SIGNAL, ++time, signal_to_remove);
			
	comm->broadcast_message(&signal);

	wait_signals[critical_section_id].erase(*signal_to_remove);
}

void synchronizer::wait_in_section(uint16_t critical_section_id, pthread_mutex_t* mutex) {
	pthread_mutex_lock(&internal_state_mutex);

	const lock_request* request_to_remove = own_requests[critical_section_id];

	wait_signal signal(MESSAGE_TAG::WAIT_SIGNAL, ++time, request_to_remove);
	wait_signals[critical_section_id].insert(signal);
	wait_signals_mutexes[signal] = mutex;
	own_wait_signals[critical_section_id] = &*wait_signals[critical_section_id].find(signal);

	comm->broadcast_message(&signal);

	lock_requests[critical_section_id].erase(*request_to_remove);
	own_requests.erase(critical_section_id);

	pthread_mutex_unlock(&internal_state_mutex);
}
