#include "../inc/communicator.h"

communicator::communicator(uint32_t process_id) {
	this->process_id = process_id;
	time = 0;
}

void communicator::send_lock_request(guarded_section_descriptor section_descriptor) {
	synchronization_request request(time, process_id, LOCK_REQUEST, time, section_descriptor.guarded_section_id);

	broadcast_sync_request(&request);
}
