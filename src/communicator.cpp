#include "../inc/communicator.h"

void communicator::sendLockRequest(pthread_mutex_t* mutex) {
	broadcastSyncRequest(1);
}
