#include "../../../synchronizer/messages/synchronization_message.h"

synchronization_message::synchronization_message() {}
synchronization_message::synchronization_message(uint16_t tag, uint32_t time): packet(tag) {
	this->time = time;
}

void synchronization_message::serialize_members(uint8_t* buf) {
	uint8_t* seek = buf;
	
	uint32_t time = htonl(this->time);
	memcpy(seek, &time, sizeof(time));
	seek += sizeof(time);

	serialize_synchronization_members(seek);	
}

void synchronization_message::deserialize_members(uint8_t* buf) {
	uint8_t* seek = buf;

	uint32_t time;
	memcpy(&time, seek, sizeof(time));
	this->time = ntohl(time);
	seek += sizeof(process_id);

	deserialize_synchronization_members(seek);
}

size_t synchronization_message::calculate_members_size() {
	return sizeof(time) + calculate_synchronization_members_size();
}

synchronization_message::~synchronization_message() {}
