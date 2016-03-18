#include "../inc/communicator.h"

void communicator::sendLockRequest(pthread_mutex_t* mutex) {
	synchronization_request request;
	broadcastRequest();
}
