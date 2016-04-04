#include "../../inc/resources_synchronizer/resources_synchronizer.h"

void resources_synchronizer::register_resources(resources* section_resources) {
	pthread_mutex_lock(&internal_state_mutex);

	sections_resources[section_resources->critical_section_id] = section_resources;	

	pthread_mutex_unlock(&internal_state_mutex);
}
