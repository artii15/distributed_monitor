#include "../../../inc/synchronizer/messages/wait_signal.h"

wait_signal::wait_signal() {}

wait_signal::wait_signal(uint8_t* buf) {
	deserialize(buf);
}

wait_signal::wait_signal(uint16_t tag, uint32_t time, const lock_request* request_to_remove): synchronization_message(tag, time) {
	this->request_to_remove = *request_to_remove;
}

void wait_signal::serialize_synchronization_members(uint8_t* buf) {
	request_to_remove.serialize(buf);
}

void wait_signal::deserialize_synchronization_members(uint8_t* serialized) {
	request_to_remove.deserialize(serialized);
}

size_t wait_signal::calculate_synchronization_members_size() {
	return request_to_remove.get_size();
}

bool wait_signal::operator>(const wait_signal& signal) const {
	return request_to_remove > signal.request_to_remove;
}

bool wait_signal::operator==(const wait_signal& signal) const {
	return request_to_remove == signal.request_to_remove;
}

bool wait_signal::operator<(const wait_signal& signal) const {
	return request_to_remove < signal.request_to_remove;
}

wait_signal::~wait_signal() {}
