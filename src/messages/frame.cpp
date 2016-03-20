#include "../../inc/messages/frame.h"
#include <string.h>

frame::frame() {
	time = 0;
	tag = 0;
	payload = NULL;
}

frame::frame(uint32_t time, uint16_t tag, packet* payload) {
	this->time = time;
	this->tag = tag;
	this->payload = payload;
}

void frame::serialize(uint8_t* buf) {
	uint8_t* seek = buf;
	
	uint32_t time = htonl(this->time);
	memcpy(seek, &time, sizeof(time));
	seek += sizeof(time);

	uint16_t tag = htons(this->tag);
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

	uint16_t tag;
	memcpy(&tag, seek, sizeof(tag));
	this->tag = ntohs(tag);
	seek += sizeof(tag);

	payload->deserialize(seek);
}

size_t frame::get_size() {
	return sizeof(time) + sizeof(tag) + payload->get_size();
}
