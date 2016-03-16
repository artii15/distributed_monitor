#include "../inc/synchronization_request.h"

synchronization_request::synchronization_request() {
	this->time = 0;
	this->pid = 0;
	this->tag = 0;
}

synchronization_request::synchronization_request(uint32_t time, uint32_t pid, uint32_t tag) {
	this->time = time;
	this->pid = pid;
	this->tag = tag;
}

bool synchronization_request::operator>(const synchronization_request& request) const {
	return time > request.time || (time == request.time && pid > request.pid);
}

bool synchronization_request::operator==(const synchronization_request& request) const {
	return time == request.time && pid == request.pid;
}

bool synchronization_request::operator<(const synchronization_request& request) const {
	return !(*this == request || *this > request);
}
