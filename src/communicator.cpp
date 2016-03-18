#include "../inc/communicator.h"

communicator::communicator(uint32_t process_id) {
	this->process_id = process_id;
	time = 0;
}

void communicator::send_lock_request(guarded_section_descriptor section_descriptor) {
	synchronization_request request(time, process_id, REQUEST_TAG::LOCK_REQUEST, time, section_descriptor.guarded_section_id);
	put_into_lock_requests(&request);

	broadcast_sync_request(&request);
}

void communicator::put_into_lock_requests(synchronization_request* request) {
	//lock_requests[LOCK_REQUEST].push(*request);
}
