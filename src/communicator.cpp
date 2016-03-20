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
		frame* message = receive_message();

		time = ((message->time > time) ? message->time : time) + 1;

		message->payload->be_handled_by(this);

		delete message;
	}
}

void communicator::handle(sync_request* request) {
	delete request;
}
