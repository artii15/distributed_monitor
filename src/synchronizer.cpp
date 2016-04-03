#include "../inc/synchronizer.h"
#include <stdio.h>

using namespace std;

synchronizer::synchronizer(communicator* comm, process_descriptor* process) {
	this->comm = comm;
	this->process = process;
}

void synchronizer::on_message(packet* message) {
	switch(message->tag) {
		/*
		case MESSAGE_TAG::LOCK_REQUEST: message->payload = new lock_request(); break;
		case MESSAGE_TAG::LOCK_RESPONSE: message->payload = new lock_response(); break;
		case MESSAGE_TAG::RELEASE_SIGNAL: message->payload = new release_signal(); break;
		case MESSAGE_TAG::WAIT_SIGNAL: message->payload = new wait_signal(); break;
		case MESSAGE_TAG::WAKE_SIGNAL: message->payload = new wake_signal(); break;
		*/
	}
}

void synchronizer::handle(lock_request* request) {
	lock_requests[request->critical_section_id].insert(*request);

	const lock_request* answer = (own_requests.find(request->critical_section_id) == own_requests.end()) ? request : own_requests[request->critical_section_id];

	++process->time;
	lock_response response(MESSAGE_TAG::LOCK_RESPONSE, process->time, request, answer);

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

		request_critical_section_access(critical_section_id, wait_signal_mutex);
	}

	wait_signals[critical_section_id].erase(*signal_to_release);
}

void synchronizer::try_to_enter(uint16_t critical_section_id) {
	map<uint16_t, const lock_request*>::iterator own_requests_iterator = own_requests.find(critical_section_id);
	if(own_requests_iterator != own_requests.end()) {
		const lock_request* own_request = own_requests_iterator->second;
		request_descriptor* descriptor = &requests_descriptors[*own_request];

		if(descriptor->number_of_confirmations == process->number_of_processes && *lock_requests[critical_section_id].begin() == *own_request) {
			pthread_mutex_unlock(descriptor->mutex);
			requests_descriptors.erase(*own_request);
		}
	}
}

void synchronizer::request_critical_section_access(uint16_t critical_section_id, pthread_mutex_t* waiting_process_mutex) {
	lock_request request(process->id, process->time, critical_section_id);
	requests_descriptors[request] = request_descriptor(waiting_process_mutex, 1);

	lock_requests[critical_section_id].insert(request);
	own_requests[critical_section_id] = &*lock_requests[critical_section_id].find(request);

	++process->time;
	comm->broadcast_message(&request);
}

void synchronizer::wake_all_in_section(uint16_t critical_section_id) {
	while(!wait_signals[critical_section_id].empty()) {
		++process->time;
		wake_one_in_section(critical_section_id);
	}
}

void synchronizer::wake_one_in_section(uint16_t critical_section_id) {
	const wait_signal* signal_to_remove = &*wait_signals[critical_section_id].begin();
	wake_signal	signal(signal_to_remove);
			
	comm->broadcast_message(&signal);

	wait_signals[critical_section_id].erase(*signal_to_remove);
}
