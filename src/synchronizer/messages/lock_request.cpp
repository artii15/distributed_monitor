#include "../../../inc/synchronizer/messages/lock_request.h"
#include <string.h>

lock_request::lock_request() {}

lock_request::lock_request(uint8_t* buf) {
	deserialize(buf);
}

lock_request::lock_request(uint16_t tag, uint32_t time, uint32_t process_id, uint16_t critical_section_id): synchronization_message(tag, time) {
	this->process_id = process_id;
	this->critical_section_id = critical_section_id;
}

bool lock_request::operator>(const lock_request& request) const {
	return time > request.time || (time == request.time && process_id > request.process_id);
}

bool lock_request::operator==(const lock_request& request) const {
	return time == request.time && process_id == request.process_id;
}

bool lock_request::operator<(const lock_request& request) const {
	return !(*this == request || *this > request);
}

void lock_request::serialize_synchronization_members(uint8_t* buf) {
	uint8_t* seek = buf;
	
	uint32_t process_id = htonl(this->process_id);
	memcpy(seek, &process_id, sizeof(process_id));
	seek += sizeof(process_id);

	uint16_t critical_section_id = htons(this->critical_section_id);
	memcpy(seek, &critical_section_id, sizeof(critical_section_id));
}

void lock_request::deserialize_synchronization_members(uint8_t* serialized) {
	uint8_t* seek = serialized;

	uint32_t process_id;
	memcpy(&process_id, seek, sizeof(process_id));
	this->process_id = ntohl(process_id);
	seek += sizeof(process_id);

	uint16_t critical_section_id;
	memcpy(&critical_section_id, seek, sizeof(critical_section_id));
	this->critical_section_id = ntohs(critical_section_id);
}

size_t lock_request::calculate_synchronization_members_size() {
	return sizeof(process_id) + sizeof(critical_section_id);
}

lock_request::~lock_request() {}
