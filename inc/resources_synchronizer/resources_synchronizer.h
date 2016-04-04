#ifndef RESOURCES_SYNCHRONIZER_H
#define RESOURCES_SYNCHRONIZER_H

#include "resources.h"
#include "../communicators/communicator.h"
#include <map>
#include <pthread.h>

class resources_synchronizer {
	public:
		resources_synchronizer(communicator*);

		void register_resources(resources*);
		resources* get_resource(uint16_t critical_section_id);
		void update(uint16_t critical_section_id);
	private:
		communicator* comm;

		std::map<uint16_t, resources*> sections_resources;
};

#endif
