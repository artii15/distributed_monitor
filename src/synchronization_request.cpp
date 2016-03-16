#include "../inc/synchronization_request.h"
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

synchronization_request::synchronization_request() {
	this->time = 0;
	this->pid = 0;
	this->tag = 0;
}

synchronization_request::synchronization_request(char* serialized) {
	char* seek = serialized;

	uint32_t time;
	memcpy(&time, seek, sizeof(time));
	this->time = ntohl(time);
	seek += sizeof(time);

	uint32_t pid;
	memcpy(&pid, seek, sizeof(pid));
	this->pid = ntohl(pid);
	seek += sizeof(pid);

	uint16_t tag;
	memcpy(&tag, seek, sizeof(tag));
	this->tag = ntohs(tag);
}

synchronization_request::synchronization_request(uint32_t time, uint32_t pid, uint16_t tag) {
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
	
	uint32_t time = htonl(this->time);
	memcpy(seek, &time, sizeof(time));
	seek += sizeof(time);

	uint32_t pid = htonl(this->pid);
	memcpy(seek, &pid, sizeof(pid));
	seek += sizeof(pid);

	uint16_t tag = htons(this->tag);
	memcpy(seek, &tag, sizeof(tag));

	return buf;
}
