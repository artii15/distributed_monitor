#include "../inc/communicator.h"

communicator::communicator(uint32_t process_id, unsigned int number_of_processes) {
	this->process_id = process_id;
	this->number_of_processes = number_of_processes;
	time = 0;
	enabled = true;
}

void communicator::send_lock_request(uint16_t critical_section_id, pthread_mutex_t* mutex) {
	sync_request request(process_id, time, critical_section_id);

	lock_requests[request.critical_section_id].push(request);
	requests_descriptors[request] = request_descriptor(mutex, 1);

	frame message(time, REQUEST_TAG::LOCK_REQUEST, &request);
	broadcast_message(&message);

	++time;
}

void communicator::listen() {
	while(enabled) {
		frame message; 
		receive_message(&message);
		time = ((message.time > time) ? message.time : time) + 1;

		handle_message(&message);
	}
}

void communicator::handle_message(frame* message) {
	switch(message->tag) {
		case REQUEST_TAG::LOCK_REQUEST: handle_lock_request(dynamic_cast<sync_request*>(message->payload)); break;
	}
}

void communicator::handle_lock_request(sync_request* request) {
}
