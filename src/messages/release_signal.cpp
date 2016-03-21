#include "../../inc/messages/release_signal.h"
#include "../../inc/communicator.h"

release_signal::release_signal() {}

release_signal::release_signal(lock_request* released_request) {
	this->released_request = *released_request;
}

void release_signal::serialize(uint8_t* buf) {
	released_request.serialize(buf);
}

void release_signal::deserialize(uint8_t* serialized) {
	released_request.deserialize(serialized);
}

size_t release_signal::get_size() {
	return released_request.get_size();
}

void release_signal::be_handled_by(communicator* comm) {
	comm->handle(this);
}

release_signal::~release_signal() {}
