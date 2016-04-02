#include "../../inc/messages/lock_response.h"

lock_response::lock_response() {}

lock_response::lock_response(uint16_t tag, uint32_t time, const lock_request* confirmed_request, const lock_request* answer): packet(tag, time) {
	this->confirmed_request = *confirmed_request;
	this->answer = *answer;
}

void lock_response::pack_into_buffer(uint8_t* buf) {
	uint8_t* seek = buf;
	confirmed_request.pack_into_buffer(seek);

	seek += confirmed_request.calculate_size();
	answer.pack_into_buffer(seek);
}

void lock_response::unpack_from_buffer(uint8_t* serialized) {
	uint8_t* seek = serialized;
	confirmed_request.unpack_from_buffer(seek);

	seek += confirmed_request.calculate_size();
	answer.unpack_from_buffer(seek);
}

size_t lock_response::calculate_size() {
	return confirmed_request.calculate_size() + answer.calculate_size();
}

lock_response::~lock_response() {}
