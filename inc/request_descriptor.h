#ifndef REQUEST_DESCRIPTOR_H
#define REQUEST_DESCRIPTOR_H

#include "synchronization_request.h"
#include <pthread.h>

class request_descriptor {
	public:
		synchronization_request request;
		pthread_mutex_t* mutex;
		unsigned int number_of_confirmations;

		request_descriptor(synchronization_request& request, pthread_mutex_t* mutex, unsigned int number_of_confirmations);

		bool operator>(const request_descriptor& descriptor) const;
};

#endif
