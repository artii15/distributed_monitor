#include "../../inc/resources_synchronizer/resources.h"
#include <string.h>

resources::resources() {}

resources::resources(uint16_t critical_section_id, uint32_t version) {
	this->critical_section_id = critical_section_id;
	this->version = version;
}

void resources::serialize(uint8_t* buf) {
	uint8_t* seek = buf;	

	uint16_t critical_section_id = htons(this->critical_section_id);
	memcpy(seek, &critical_section_id, sizeof(critical_section_id));
	seek += sizeof(critical_section_id);
	
	uint32_t version = htonl(this->version);
	memcpy(seek, &version, sizeof(version));
	seek += sizeof(version);

	serialize_resources_members(seek);
}

void resources::deserialize(uint8_t* buf) {
	uint8_t* seek = buf;

	uint16_t critical_section_id;
	memcpy(&critical_section_id, seek, sizeof(critical_section_id));
	this->critical_section_id = ntohs(critical_section_id);
	seek += sizeof(critical_section_id);

	uint32_t version;
	memcpy(&version, seek, sizeof(version));
	this->version = ntohl(version);
	seek += sizeof(version);

	deserialize_resources_members(seek);
}

size_t resources::get_size() {
	return sizeof(version) + calculate_resources_members_size();
}
