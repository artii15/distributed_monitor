#ifndef SYNCHRONIZATION_REQUEST_H
#define SYNCHRONIZATION_REQUEST_H

#include <stdint.h>

class synchronization_request {
	public:
		uint32_t time;
		uint32_t pid;
		uint16_t tag;

		synchronization_request();
		synchronization_request(char*);
		synchronization_request(uint32_t time, uint32_t pid, uint16_t tag);

		bool operator>(const synchronization_request& request) const;

		bool operator==(const synchronization_request& request) const;

		bool operator<(const synchronization_request& request) const;

		char* serialize();

		static unsigned int size;
};

#endif
