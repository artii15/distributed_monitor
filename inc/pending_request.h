#ifndef PENDING_REQUEST_H
#define PENDING_REQUEST_H

#include "synchronization_request.h"
#include <pthread.h>

struct pending_request {
	synchronization_request* request;
	pthread_mutex_t* mutex;
	unsigned int number_of_confirmations;
};

#endif
