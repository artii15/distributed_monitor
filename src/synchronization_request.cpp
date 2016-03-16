#include "../inc/synchronization_request.h"
#include <stdlib.h>
#include <string.h>

synchronization_request::synchronization_request() {
	this->time = 0;
	this->pid = 0;
	this->tag = 0;
}

synchronization_request::synchronization_request(char* serialized) {
	char* seek = serialized;

	memcpy(&time, seek, sizeof(time));
	seek += sizeof(time);

	memcpy(&pid, seek, sizeof(pid));
	seek += sizeof(pid);

	memcpy(&tag, seek, sizeof(tag));
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

char* synchronization_request::serialize() {
	char* buf = (char*)malloc(sizeof(time) + sizeof(pid) + sizeof(tag));
	char* seek = buf;
	
	memcpy(seek, &time, sizeof(time));
	seek += sizeof(time);

	memcpy(seek, &pid, sizeof(pid));
	seek += sizeof(pid);

	memcpy(seek, &tag, sizeof(tag));

	return buf;
}
