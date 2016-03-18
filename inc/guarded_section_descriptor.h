#ifndef GUARDED_SECTION_DESCRIPTIOR_H
#define GUARDED_SECTION_DESCRIPTIOR_H

#include <stdint.h>
#include <pthread.h>

struct guarded_section_descriptor {
	uint16_t guarded_section_id;
	pthread_mutex_t* mutex;

	guarded_section_descriptor(uint16_t guarded_section_id, pthread_mutex_t* mutex) {
		this->guarded_section_id = guarded_section_id;
		this->mutex = mutex;
	}
};

#endif
