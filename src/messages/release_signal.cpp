#include "../../inc/messages/release_signal.h"

release_signal::release_signal() {}

release_signal::release_signal(const lock_request* released_request) {
	this->released_request = *released_request;
}

void release_signal::serialize_members(uint8_t* buf) {
	released_request.serialize(buf);
}

void release_signal::deserialize_members(uint8_t* serialized) {
	released_request.deserialize(serialized);
}

size_t release_signal::calculate_members_size() {
	return released_request.get_size();
}

release_signal::~release_signal() {}
