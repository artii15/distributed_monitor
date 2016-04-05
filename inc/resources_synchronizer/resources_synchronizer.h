#ifndef RESOURCES_SYNCHRONIZER_H
#define RESOURCES_SYNCHRONIZER_H

#include "resources.h"
#include "../communicators/communicator.h"
#include "../communicators/message_handler.h"
#include <map>
#include <pthread.h>

class resources_synchronizer: public message_handler {
	public:
		resources_synchronizer(communicator*);

		void register_resources(resources*);
		resources* get_resource(uint16_t critical_section_id);
		void update(uint16_t critical_section_id);

		virtual void handle(uint8_t* raw_message, uint16_t tag);
	private:
		communicator* comm;

		std::map<uint16_t, resources*> sections_resources;
};

#endif
