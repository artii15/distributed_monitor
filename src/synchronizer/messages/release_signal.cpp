#include "../../../inc/synchronizer/messages/release_signal.h"

release_signal::release_signal() {}

release_signal::release_signal(uint8_t* buf) {
	deserialize(buf);
}

release_signal::release_signal(uint16_t tag, uint32_t time, const lock_request* released_request): synchronization_message(tag, time) {
	this->released_request = *released_request;
}

void release_signal::serialize_synchronization_members(uint8_t* buf) {
	released_request.serialize(buf);
}

void release_signal::deserialize_synchronization_members(uint8_t* serialized) {
	released_request.deserialize(serialized);
}

size_t release_signal::calculate_synchronization_members_size() {
	return released_request.get_size();
}

release_signal::~release_signal() {}
