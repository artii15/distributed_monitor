#include "../../inc/messages/lock_response.h"

lock_response::lock_response() {}

lock_response::lock_response(uint16_t tag, uint32_t time, const lock_request* confirmed_request, const lock_request* answer): packet(tag, time) {
	this->confirmed_request = *confirmed_request;
	this->answer = *answer;
}

lock_response::lock_response(uint8_t* buf) {
	deserialize(buf);
}

void lock_response::serialize_members(uint8_t* buf) {
	uint8_t* seek = buf;
	confirmed_request.serialize(seek);

	seek += confirmed_request.get_size();
	answer.serialize(seek);
}

void lock_response::deserialize_members(uint8_t* serialized) {
	uint8_t* seek = serialized;
	confirmed_request.deserialize(seek);

	seek += confirmed_request.get_size();
	answer.deserialize(seek);
}

size_t lock_response::calculate_members_size() {
	return confirmed_request.get_size() + answer.get_size();
}

lock_response::~lock_response() {}
