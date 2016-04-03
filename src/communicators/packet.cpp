#include "../../inc/communicators/packet.h"
#include <string.h>

packet::packet() {}

packet::packet(uint16_t tag) {
	this->tag = tag;
}

void packet::serialize(uint8_t* buf) {
	uint8_t* seek = buf;	
	
	uint16_t tag= htons(this->tag);
	memcpy(seek, &tag, sizeof(tag));
	seek += sizeof(tag);

	serialize_members(seek);
}

void packet::deserialize(uint8_t* buf) {
	uint8_t* seek = buf;

	uint16_t tag;
	memcpy(&tag, seek, sizeof(tag));
	this->tag = ntohs(tag);
	seek += sizeof(tag);

	deserialize_members(seek);
}

size_t packet::get_size() {
	return sizeof(tag) + calculate_members_size();
}
