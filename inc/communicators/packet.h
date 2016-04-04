#ifndef PACKET_H
#define PACKET_H

#include <arpa/inet.h>
#include "../serializable.h"

class packet: public serializable {
	public:
		uint16_t tag;

		packet();
		packet(uint16_t tag);

		virtual void serialize(uint8_t* buf);
		virtual void deserialize(uint8_t* buf);
		size_t get_size();
	protected:
		virtual void serialize_members(uint8_t* buf) = 0;
		virtual void deserialize_members(uint8_t* buf) = 0;
		virtual size_t calculate_members_size() = 0;
};

#endif
