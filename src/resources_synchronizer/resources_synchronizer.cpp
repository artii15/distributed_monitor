#include "../../inc/resources_synchronizer/resources_synchronizer.h"

resources_synchronizer::resources_synchronizer(communicator* comm) {
	this->comm = comm;
}

void resources_synchronizer::register_resources(resources* section_resources) {
	sections_resources[section_resources->critical_section_id] = section_resources;	
}

resources* resources_synchronizer::get_resource(uint16_t critical_section_id) {
	return sections_resources[critical_section_id];
}

void resources_synchronizer::update(uint16_t critical_section_id) {
}
