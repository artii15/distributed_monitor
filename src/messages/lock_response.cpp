#include "../../inc/messages/lock_response.h"
#include "../../inc/communicator.h"

lock_response::lock_response() {}

lock_response::lock_response(const lock_request* confirmed_request, const lock_request* top_request) {
	this->confirmed_request = *confirmed_request;
	this->top_request = *top_request;
}

void lock_response::serialize(uint8_t* buf) {
	uint8_t* seek = buf;
	confirmed_request.serialize(seek);

	seek += confirmed_request.get_size();
	top_request.serialize(seek);
}

void lock_response::deserialize(uint8_t* serialized) {
	uint8_t* seek = serialized;
	confirmed_request.deserialize(seek);

	seek += confirmed_request.get_size();
	top_request.deserialize(seek);
}

size_t lock_response::get_size() {
	return confirmed_request.get_size() + top_request.get_size();
}


void lock_response::be_handled_by(communicator* comm) {
	comm->handle(this);
}

lock_response::~lock_response() {}
