#include "../inc/communicator.h"
#include "../inc/exceptions/invalid_message_exception.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

communicator::communicator(uint32_t process_id, unsigned int number_of_processes) {
	this->process_id = process_id;
	this->number_of_processes = number_of_processes;
	time = 0;
	enabled = true;
}

void communicator::send_lock_request(uint16_t critical_section_id, pthread_mutex_t* waiting_process_mutex) {
	pthread_mutex_lock(&internal_state_mutex);

	request_critical_section_access(critical_section_id, waiting_process_mutex);

	pthread_mutex_unlock(&internal_state_mutex);
}

void communicator::request_critical_section_access(uint16_t critical_section_id, pthread_mutex_t* waiting_process_mutex) {
	printf("Process: %d, Time: %d, Trying to enter section %d\n", process_id, time, critical_section_id);

	lock_request request(process_id, time, critical_section_id);
	requests_descriptors[request] = request_descriptor(waiting_process_mutex, 1);

	lock_requests[critical_section_id].insert(request);
	own_requests[critical_section_id] = &*lock_requests[critical_section_id].find(request);

	++time;
	frame message(time, MESSAGE_TAG::LOCK_REQUEST, &request);
	broadcast_message(&message);
}

void communicator::listen() {
	while(enabled) {
		receive_message();
/*
		pthread_mutex_lock(&internal_state_mutex);

		time = ((message->time > time) ? message->time : time) + 1;
		message->payload->be_handled_by(this);

		pthread_mutex_unlock(&internal_state_mutex);
*/
	}
}

void communicator::handle(uint8_t* raw_message, uint16_t tag) {
/*
	switch(tag) {
		case MESSAGE_TAG::LOCK_REQUEST: {
			lock_request message;
			message.deserialize(raw_message);
			handle(&message);
			break;
		}
		case MESSAGE_TAG::LOCK_RESPONSE: {
			lock_response message;
			message.payload = &payload;
			message.deserialize(raw_message);
			handle(&message);
			break;
		}
		case MESSAGE_TAG::RELEASE_SIGNAL: {
			release_signal payload;
			message.payload = &payload;
			message.deserialize(raw_message);
			handle(&message);
			break;
		}
		case MESSAGE_TAG::WAIT_SIGNAL: {
			wait_signal payload;
			message.payload = &payload;
			message.deserialize(raw_message);
			handle(&message);
			break;
		}
		case MESSAGE_TAG::WAKE_SIGNAL: {
			wake_signal payload;
			message.payload = &payload;
			message.deserialize(raw_message);
			handle(&message);
			break;
		}
		default: throw invalid_message_exception("Not recognized message arrived");
	}
*/
}

void communicator::handle(packet* message) {
				
}

void communicator::send_release_signal(uint16_t critical_section_id) {
	pthread_mutex_lock(&internal_state_mutex);
	const lock_request* request_to_release = own_requests[critical_section_id];

	++time;
	release_signal request_release_signal(request_to_release);
	frame message(time, MESSAGE_TAG::RELEASE_SIGNAL, &request_release_signal);
	broadcast_message(&message);

	own_requests.erase(critical_section_id);
	lock_requests[critical_section_id].erase(*request_to_release);

	pthread_mutex_unlock(&internal_state_mutex);
}

void communicator::send_wait_signal(uint16_t critical_section_id, pthread_mutex_t* mutex) {
	pthread_mutex_lock(&internal_state_mutex);

	++time;
	const lock_request* request_to_remove = own_requests[critical_section_id];

	wait_signal signal(request_to_remove);
	wait_signals[critical_section_id].insert(signal);
	wait_signals_mutexes[signal] = mutex;
	own_wait_signals[critical_section_id] = &*wait_signals[critical_section_id].find(signal);

	frame message(time, MESSAGE_TAG::WAIT_SIGNAL, &signal);
	broadcast_message(&message);

	lock_requests[critical_section_id].erase(*request_to_remove);
	own_requests.erase(critical_section_id);

	pthread_mutex_unlock(&internal_state_mutex);
}

void communicator::send_wake_signal(uint16_t critical_section_id) {
	pthread_mutex_lock(&internal_state_mutex);

	if(!wait_signals[critical_section_id].empty()) {
		++time;
		wake_one_in_section(critical_section_id);
	}

	pthread_mutex_unlock(&internal_state_mutex);
}

void communicator::send_wake_all_signal(uint16_t critical_section_id) {
	pthread_mutex_lock(&internal_state_mutex);

	while(!wait_signals[critical_section_id].empty()) {
		++time;
		wake_one_in_section(critical_section_id);
	}

	pthread_mutex_unlock(&internal_state_mutex);
}

void communicator::wake_one_in_section(uint16_t critical_section_id) {
	const wait_signal* signal_to_remove = &*wait_signals[critical_section_id].begin();
	wake_signal	signal(signal_to_remove);
			
	frame message(time, MESSAGE_TAG::WAKE_SIGNAL, &signal);
	broadcast_message(&message);

	wait_signals[critical_section_id].erase(*signal_to_remove);
}

communicator::~communicator() {
	pthread_mutex_destroy(&internal_state_mutex);	
}
