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

		resources_update message(MESSAGE_TAG::RESOURCES_UPDATE, critical_section_id, res);
		comm->broadcast_message(&message);
	}
}

void resources_synchronizer::handle(uint8_t* raw_message, uint16_t tag) {

}
