#include "../inc/communicator.h"

communicator::communicator(uint32_t process_id, unsigned int number_of_processes) {
	this->process_id = process_id;
	this->number_of_processes = number_of_processes;
	time = 0;
	enabled = true;
}

void communicator::send_lock_request(uint16_t guarded_section_id, pthread_mutex_t* mutex) {
	synchronization_request request(time, process_id, REQUEST_TAG::LOCK_REQUEST, time, guarded_section_id);

	lock_requests[request.guarded_section_id].push(request);

	broadcast_sync_request(&request);
	++time;
}

void communicator::listen() {
	while(enabled) {
		synchronization_request message; 
		receive_message(&message);
		time = ((message.time > time) ? message.time : time) + 1;

		handle_message(&message);
	}
}

void communicator::handle_message(synchronization_request* message) {
	switch(message->tag) {
		case REQUEST_TAG::LOCK_REQUEST: handle_lock_request(message); break;
	}
}

void communicator::handle_lock_request(synchronization_request* request) {
}
