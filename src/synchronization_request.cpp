#include "../inc/synchronization_request.h"
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

unsigned int synchronization_request::size = sizeof(time) + sizeof(pid) + sizeof(tag) + sizeof(creation_time) + sizeof(guarded_section_id);

synchronization_request::synchronization_request() {
	this->time = 0;
	this->pid = 0;
	this->tag = 0;
	this->creation_time = 0;
	this->guarded_section_id = 0;
}

synchronization_request::synchronization_request(uint8_t* serialized) {
	uint8_t* seek = serialized;

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
	seek += sizeof(tag);

	uint32_t creation_time;
	memcpy(&creation_time, seek, sizeof(creation_time));
	this->creation_time = ntohl(creation_time);
	seek += sizeof(creation_time);

	uint16_t guarded_section_id;
	memcpy(&guarded_section_id, seek, sizeof(guarded_section_id));
	this->guarded_section_id = ntohs(guarded_section_id);
}

synchronization_request::synchronization_request(uint32_t time, uint32_t pid, uint16_t tag, uint32_t creation_time, uint16_t guarded_section_id) {
	this->time = time;
	this->pid = pid;
	this->tag = tag;
	this->creation_time = creation_time;
	this->guarded_section_id = guarded_section_id;
}

bool synchronization_request::operator>(const synchronization_request& request) const {
	return creation_time > request.creation_time || (creation_time == request.creation_time && pid > request.pid);
}

bool synchronization_request::operator==(const synchronization_request& request) const {
	return creation_time == request.creation_time && pid == request.pid;
}

bool synchronization_request::operator<(const synchronization_request& request) const {
	return !(*this == request || *this > request);
}

void synchronization_request::serialize(uint8_t* buf) {
	uint8_t* seek = buf;
	
	uint32_t time = htonl(this->time);
	memcpy(seek, &time, sizeof(time));
	seek += sizeof(time);

	uint32_t pid = htonl(this->pid);
	memcpy(seek, &pid, sizeof(pid));
	seek += sizeof(pid);

	uint16_t tag = htons(this->tag);
	memcpy(seek, &tag, sizeof(tag));
	seek += sizeof(tag);

	uint32_t creation_time = htonl(this->creation_time);
	memcpy(seek, &creation_time, sizeof(creation_time));
	seek += sizeof(creation_time);

	uint16_t guarded_section_id = htons(this->guarded_section_id);
	memcpy(seek, &guarded_section_id, sizeof(guarded_section_id));
}
