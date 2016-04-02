#include "../../inc/messages/packet.h"

packet::packet() {
	tag = 0;
	time = 0;
}

packet::packet(uint16_t tag, uint32_t time) {
	this->tag = tag;
	this->time = time;
}

void packet::serialize(uint8_t* buf) {
	uint8_t* seek = buf;	
	
	uint16_t tag= htons(this->tag);
	memcpy(seek, &tag, sizeof(tag));
	seek += sizeof(tag);

	uint32_t time = htonl(this->time);
	memcpy(seek, &time, sizeof(time));
	seek += sizeof(time);

	pack_into_buffer(seek);
}

void packet::deserialize(uint8_t* buf) {
	uint8_t* seek = buf;

	uint16_t tag;
	memcpy(&tag, seek, sizeof(tag));
	this->tag = ntohs(tag);
	seek += sizeof(tag);

	uint32_t time;
	memcpy(&time, seek, sizeof(time));
	this->time = ntohl(time);
	seek += sizeof(time);

	unpack_from_buffer(seek);
}

size_t packet::get_size() {
	return sizeof(tag) + sizeof(time) + calculate_size();
}
