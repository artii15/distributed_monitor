#ifndef RESOURCES_SYNCHRONIZER_H
#define RESOURCES_SYNCHRONIZER_H

#include "resources.h"
#include <map>
#include <pthread.h>

class resources_synchronizer {
	public:
		void register_resources(resources*);
		resources* acquire(uint16_t critical_section_id);
	private:
		std::map<uint16_t, resources*> sections_resources;
		pthread_mutex_t internal_state_mutex = PTHREAD_MUTEX_INITIALIZER;
};

#endif
