#ifndef REQUEST_DESCRIPTOR_H
#define REQUEST_DESCRIPTOR_H

#include "synchronization_request.h"
#include <pthread.h>

class request_descriptor {
	public:
		pthread_mutex_t* mutex;
		unsigned int number_of_confirmations;

		request_descriptor();
		request_descriptor(pthread_mutex_t* mutex, unsigned int number_of_confirmations);
};

#endif
