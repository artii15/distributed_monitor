#include "../../inc/resources_synchronizer/resources_synchronizer.h"
#include "../../inc/resources_synchronizer/messages/resources_update.h"
#include "../../inc/messages_tags.h"
#include "../../inc/exceptions/unknown_resource_exception.h"
#include <stdio.h>
#include <unistd.h>

using namespace std;

resources_synchronizer::resources_synchronizer(communicator* comm) {
	this->comm = comm;
	comm->register_message_handler(MESSAGE_TAG::RESOURCES_UPDATE, this);
}

void resources_synchronizer::register_resources(resources* res) {
	sections_resources[res->critical_section_id] = res;	
}

resources* resources_synchronizer::get_resource(uint16_t critical_section_id) {
	return sections_resources[critical_section_id];
}

void resources_synchronizer::update(uint16_t critical_section_id) {
	resources* res = sections_resources[critical_section_id];
	printf("trying to update resources %u, %d, %u\n", res->version, (int)res->is_dirty, res->get_size());sleep(1);
	if(res->is_dirty) {
		++res->version;
		res->is_dirty = false;

		uint32_t res_size = res->get_size();
		uint8_t raw_res[res_size];
		res->serialize(raw_res);
		
		resources_update message(MESSAGE_TAG::RESOURCES_UPDATE, critical_section_id, raw_res, res_size);
		comm->broadcast_message(&message);
	}
}

void resources_synchronizer::handle(uint8_t* raw_message, uint16_t tag) {
	resources_update message;
	message.deserialize(raw_message);

	map<uint16_t, resources*>::iterator res_to_update = sections_resources.find(message.critical_section_id);

	if(res_to_update == sections_resources.end()) {
		throw unknown_resource_exception("Not registered resource update arrived");
	}
	else {
		res_to_update->second->update(message.raw_resources);
	}
}
