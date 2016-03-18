#include "../inc/communicator.h"

communicator::communicator(uint32_t process_id, unsigned int number_of_processes) {
	this->process_id = process_id;
	this->number_of_processes = number_of_processes;
	time = 0;
	enabled = true;
}

void communicator::send_lock_request(guarded_section_descriptor section_descriptor) {
	synchronization_request* request = new synchronization_request(time, process_id, REQUEST_TAG::LOCK_REQUEST, time, section_descriptor.guarded_section_id);

	lock_requests[request->guarded_section_id].push(pending_request(request, section_descriptor.mutex, 1));

	broadcast_sync_request(request);
}

void communicator::listen() {
	while(enabled) {
		synchronization_request* message = receive_message();
		handle_message(message);
	}
}

void communicator::handle_message(synchronization_request* message) {
	switch(message->tag) {
		case REQUEST_TAG::LOCK_REQUEST: handle_lock_request(message); break;
	}
}

void communicator::handle_lock_request(synchronization_request* request) {

}
