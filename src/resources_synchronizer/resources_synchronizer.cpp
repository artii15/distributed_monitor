#include "../../inc/resources_synchronizer/resources_synchronizer.h"

void resources_synchronizer::register_resources(resources* section_resources) {
	sections_resources[section_resources->critical_section_id] = section_resources;	
}
