#ifndef PROCESS_DESCRIPTOR_H
#define PROCESS_DESCRIPTOR_H

#include <stdint.h>
#include <pthread.h>

class process_descriptor {
	public:
		process_descriptor(uint32_t id);

		uint32_t id;
		uint16_t time;
		pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
};

#endif
