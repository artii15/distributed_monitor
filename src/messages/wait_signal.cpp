#include "../../inc/messages/wait_signal.h"
#include "../../inc/communicator.h"

wait_signal::wait_signal() {}

wait_signal::wait_signal(const lock_request* request_to_remove) {
	this->request_to_remove = *request_to_remove;
}

void wait_signal::serialize(uint8_t* buf) {
	request_to_remove.serialize(buf);
}

void wait_signal::deserialize(uint8_t* serialized) {
	request_to_remove.deserialize(serialized);
}

size_t wait_signal::get_size() {
	return request_to_remove.get_size();
}

void wait_signal::be_handled_by(communicator* comm) {
	comm->handle(this);
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
