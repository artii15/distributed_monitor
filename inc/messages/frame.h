#ifndef FRAME_H
#define FRAME_H

#include "serializable.h"

class frame: public serializable {
	public:
		uint32_t time;
		uint8_t tag;
		serializable* payload;
		
		frame(uint32_t time, uint8_t tag);
		virtual void serialize(uint8_t* buf);
		virtual void deserialize(uint8_t* serialized);
		virtual size_t get_size();
};

#endif
