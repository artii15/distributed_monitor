#include "../../inc/resources_synchronizer/resources_synchronizer.h"
#include "../../inc/resources_synchronizer/messages/resources_update.h"
#include "../../inc/messages_tags.h"

resources_synchronizer::resources_synchronizer(communicator* comm) {
	this->comm = comm;
}

void resources_synchronizer::register_resources(resources* res) {
	sections_resources[res->critical_section_id] = res;	
}

resources* resources_synchronizer::get_resource(uint16_t critical_section_id) {
	return sections_resources[critical_section_id];
}

void resources_synchronizer::update(uint16_t critical_section_id) {
	resources* res = sections_resources[critical_section_id];
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

	resources* res_to_update = sections_resources[message.critical_section_id];

	res_to_update->update(message.raw_resources);
}
