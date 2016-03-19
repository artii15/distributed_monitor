#include "../../inc/messages/sync_request.h"
#include <string.h>

sync_request::sync_request() {
	process_id = 0;
	creation_time = 0;
	critical_section_id = 0;
}

sync_request::sync_request(uint32_t process_id, uint32_t creation_time, uint16_t critical_section_id) {
	this->process_id = process_id;
	this->creation_time = creation_time;
	this->critical_section_id = critical_section_id;
}

bool sync_request::operator>(const sync_request& request) const {
	return creation_time > request.creation_time || (creation_time == request.creation_time && process_id > request.process_id);
}

bool sync_request::operator==(const sync_request& request) const {
	return creation_time == request.creation_time && process_id == request.process_id;
}

bool sync_request::operator<(const sync_request& request) const {
	return !(*this == request || *this > request);
}

void sync_request::serialize(uint8_t* buf) {
	uint8_t* seek = buf;
	
	uint32_t process_id = htonl(this->process_id);
	memcpy(seek, &process_id, sizeof(process_id));
	seek += sizeof(process_id);

	uint32_t creation_time = htonl(this->creation_time);
	memcpy(seek, &creation_time, sizeof(creation_time));
	seek += sizeof(creation_time);

	uint16_t critical_section_id = htons(this->critical_section_id);
	memcpy(seek, &critical_section_id, sizeof(critical_section_id));
}

void sync_request::deserialize(uint8_t* serialized) {
	uint8_t* seek = serialized;

	uint32_t process_id;
	memcpy(&process_id, seek, sizeof(process_id));
	this->process_id = ntohl(process_id);
	seek += sizeof(process_id);

	uint32_t creation_time;
	memcpy(&creation_time, seek, sizeof(creation_time));
	this->creation_time = ntohl(creation_time);
	seek += sizeof(creation_time);

	uint16_t critical_section_id;
	memcpy(&critical_section_id, seek, sizeof(critical_section_id));
	this->critical_section_id = ntohs(critical_section_id);
}

size_t sync_request::get_size() {
	return sizeof(process_id) + sizeof(creation_time) + sizeof(critical_section_id);
}
