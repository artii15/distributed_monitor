#include "../inc/communicator.h"

void communicator::sendLockRequest(uint16_t guarded_section_id, pthread_mutex_t* mutex) {
	broadcastSyncRequest(guarded_section_id, LOCK_REQUEST);
}
