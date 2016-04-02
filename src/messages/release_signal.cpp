#include "../../inc/messages/release_signal.h"

release_signal::release_signal() {}

release_signal::release_signal(const lock_request* released_request) {
	this->released_request = *released_request;
}

void release_signal::pack_into_buffer(uint8_t* buf) {
	released_request.pack_into_buffer(buf);
}

void release_signal::unpack_from_buffer(uint8_t* serialized) {
	released_request.unpack_from_buffer(serialized);
}

size_t release_signal::calculate_size() {
	return released_request.calculate_size();
}

release_signal::~release_signal() {}
