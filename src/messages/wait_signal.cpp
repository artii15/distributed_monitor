#include "../../inc/messages/wait_signal.h"

wait_signal::wait_signal() {}

wait_signal::wait_signal(const lock_request* request_to_remove) {
	this->request_to_remove = *request_to_remove;
}

void wait_signal::pack_into_buffer(uint8_t* buf) {
	request_to_remove.pack_into_buffer(buf);
}

void wait_signal::unpack_from_buffer(uint8_t* serialized) {
	request_to_remove.unpack_from_buffer(serialized);
}

size_t wait_signal::calculate_size() {
	return request_to_remove.calculate_size();
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
