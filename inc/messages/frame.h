#ifndef FRAME_H
#define FRAME_H

#include "serializable.h"
#include "packet.h"

class frame: public serializable {
	public:
		uint32_t time;
		uint16_t tag;
		packet* payload;
		
		frame();
		frame(uint32_t time, uint16_t tag, packet* payload);
		virtual void serialize(uint8_t* buf);
		virtual void deserialize(uint8_t* serialized);
		virtual size_t get_size();
};

#endif
