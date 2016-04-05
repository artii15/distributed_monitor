#include "../../../inc/resources_synchronizer/messages/resources_update.h"
#include <string.h>

resources_update::resources_update() {}
resources_update::resources_update(uint16_t tag, uint16_t critical_section_id, uint8_t* raw_resources, uint32_t raw_resources_size): packet(tag) {
	this->critical_section_id = critical_section_id;
	this->raw_resources = raw_resources;
	this->raw_resources_size = raw_resources_size;
}

void resources_update::serialize_members(uint8_t* buf) {
	uint8_t* seek = buf;	
	
	uint16_t critical_section_id = htons(this->critical_section_id);
	memcpy(seek, &critical_section_id, sizeof(critical_section_id));
	seek += sizeof(critical_section_id);

	uint32_t raw_resources_size = htonl(this->raw_resources_size);
	memcpy(seek, &raw_resources_size, sizeof(raw_resources_size));
	seek += sizeof(raw_resources_size);

	memcpy(seek, this->raw_resources, this->raw_resources_size);
	seek += raw_resources_size;
}

void resources_update::deserialize_members(uint8_t* buf) {
	uint8_t* seek = buf;

	uint16_t critical_section_id;
	memcpy(&critical_section_id, seek, sizeof(critical_section_id));
	this->critical_section_id = ntohs(critical_section_id);
	seek += sizeof(critical_section_id);

	uint32_t raw_resources_size;
	memcpy(&raw_resources_size, seek, sizeof(raw_resources_size));
	this->raw_resources_size = ntohl(raw_resources_size);
	seek += sizeof(raw_resources_size);

	memcpy(this->raw_resources, seek, this->raw_resources_size);
	seek += this->raw_resources_size;
}

size_t resources_update::calculate_members_size() {
	return sizeof(critical_section_id) + raw_resources_size + sizeof(raw_resources_size);
}
