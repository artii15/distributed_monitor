#include "../inc/communicator.h"

void communicator::sendLockRequest(guarded_section_descriptor section_descriptor) {
	broadcastSyncRequest(section_descriptor.guarded_section_id, LOCK_REQUEST);
}
