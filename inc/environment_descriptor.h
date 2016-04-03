#ifndef ENVIRONMENT_DESCRIPTOR_H
#define ENVIRONMENT_DESCRIPTOR_H

#include <stdint.h>

struct environment_descriptor {
	uint32_t process_id;
	unsigned int number_of_processes;
};

#endif
