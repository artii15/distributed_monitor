#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>
#include <arpa/inet.h>

class packet {
	public:
		uint16_t tag;
		uint32_t time;

		packet();
		packet(uint16_t tag, uint32_t time);

		virtual void serialize(uint8_t* buf);
		virtual void deserialize(uint8_t* buf);
		virtual size_t get_size();
	protected:
		virtual size_t calculate_size() = 0;
		virtual void pack_into_buffer(uint8_t* buf) = 0;
		virtual void unpack_from_buffer(uint8_t* buf) = 0;
};

#endif
