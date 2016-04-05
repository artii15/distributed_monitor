#include "../../../inc/resources_synchronizer/messages/resources_update.h"
#include <string.h>

resources_update::resources_update() {}
resources_update::resources_update(uint16_t tag, uint16_t critical_section_id, resources* res): packet(tag) {
	this->critical_section_id = critical_section_id;
	this->res = res;
}

void resources_update::serialize_members(uint8_t* buf) {
	uint8_t* seek = buf;	
	
	uint16_t critical_section_id = htons(this->critical_section_id);
	memcpy(seek, &critical_section_id, sizeof(critical_section_id));
	seek += sizeof(critical_section_id);

	res->serialize(buf);
}

void resources_update::deserialize_members(uint8_t* buf) {
	uint8_t* seek = buf;

	uint16_t critical_section_id;
	memcpy(&critical_section_id, seek, sizeof(critical_section_id));
	this->critical_section_id = ntohs(critical_section_id);
	seek += sizeof(critical_section_id);

	res->deserialize(seek);
}

size_t resources_update::calculate_members_size() {
	return sizeof(critical_section_id) + res->get_size();
}
