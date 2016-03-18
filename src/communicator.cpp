#include "../inc/communicator.h"

communicator::communicator(uint32_t process_id, unsigned int number_of_processes) {
	this->process_id = process_id;
	this->number_of_processes = number_of_processes;
	time = 0;
}

void communicator::send_lock_request(guarded_section_descriptor section_descriptor) {
	synchronization_request* request = new synchronization_request(time, process_id, REQUEST_TAG::LOCK_REQUEST, time, section_descriptor.guarded_section_id);

	lock_requests[request->guarded_section_id].push(pending_request(request, section_descriptor.mutex, 1));

	broadcast_sync_request(request);
}

void communicator::listen() {
	synchronization_request* message = receive_message();
}
