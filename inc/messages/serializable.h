#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <stdint.h>
#include <arpa/inet.h>

class serializable {
	public:
		virtual void serialize(uint8_t* buf) = 0;
		virtual void deserialize(uint8_t* buf) = 0;
		virtual size_t get_size() = 0;
};

#endif
