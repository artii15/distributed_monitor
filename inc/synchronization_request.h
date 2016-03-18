#ifndef SYNCHRONIZATION_REQUEST_H
#define SYNCHRONIZATION_REQUEST_H

#include <stdint.h>

class synchronization_request {
	public:
		uint32_t time;
		uint32_t pid;
		uint16_t tag;
		uint32_t creation_time;
		uint16_t guarded_section_id;

		synchronization_request();
		synchronization_request(char*);
		synchronization_request(uint32_t time, uint32_t pid, uint16_t tag, uint32_t creation_time, uint16_t guarded_section_id);

		bool operator>(const synchronization_request& request) const;
		bool operator==(const synchronization_request& request) const;
		bool operator<(const synchronization_request& request) const;

		char* serialize();

		static unsigned int size;
};

#endif
