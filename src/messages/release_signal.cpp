#include "../../inc/messages/release_signal.h"

release_signal::release_signal() {}

release_signal::release_signal(lock_request* released_request) {
	this->released_request = *released_request;
}

void release_signal::serialize(uint8_t* buf) {
	released_request.serialize(buf);
}

void deserialize(uint8_t* serialized) {
	released_request.deserialize(serialized);
}

size_t get_size() {
	return released_request.get_size();
}

virtual void be_handled_by(communicator*) {
	communicator->handle(this);
}

release_signal::~release_signal() {}
