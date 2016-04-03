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

		void serialize(uint8_t* buf);
		void deserialize(uint8_t* buf);
		size_t get_size();
	protected:
		virtual void serialize_members(uint8_t* buf) = 0;
		virtual void deserialize_members(uint8_t* buf) = 0;
		virtual size_t calculate_members_size() = 0;
};

#endif
