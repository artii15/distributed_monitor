#include "../../inc/messages/frame.h"
#include <string.h>

frame::frame(uint32_t time, uint8_t tag) {
	this->time = time;
	this->tag = tag;
}


void frame::serialize(uint8_t* buf) {
	uint8_t* seek = buf;
	
	uint32_t time = htonl(this->time);
	memcpy(seek, &time, sizeof(time));
	seek += sizeof(time);

	uint8_t tag = htonl(this->tag);
	memcpy(seek, &tag, sizeof(tag));
	seek += sizeof(tag);

	payload->serialize(seek);
}

void frame::deserialize(uint8_t* serialized) {
	uint8_t* seek = serialized;

	uint32_t time;
	memcpy(&time, seek, sizeof(time));
	this->time = ntohl(time);
	seek += sizeof(time);

	uint8_t tag;
	memcpy(&tag, seek, sizeof(tag));
	this->tag = ntohl(tag);
	seek += sizeof(tag);

	payload->deserialize(seek);
}

size_t frame::get_size() {
	return sizeof(time) + sizeof(tag) + payload->get_size();
}
