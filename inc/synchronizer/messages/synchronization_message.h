#ifndef SYNCHRONIZATION_MESSAGE_H
#define SYNCHRONIZATION_MESSAGE_H

#include "../../communicators/packet.h"

class synchronization_message: public packet {
	public:
		uint32_t time;

		synchronization_message();
		synchronization_message(uint16_t tag, uint32_t time);

		virtual ~synchronization_message();
	protected:
		virtual void serialize_members(uint8_t* buf);
		virtual void deserialize_members(uint8_t* buf);
		virtual size_t calculate_members_size();

		virtual void serialize_synchronization_members(uint8_t* buf) = 0;
		virtual void deserialize_synchronization_members(uint8_t* buf) = 0;
		virtual size_t calculate_synchronization_members_size() = 0;
};

#endif
