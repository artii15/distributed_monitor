#ifndef RESOURCES_UPDATE_H
#define RESOURCES_UPDATE_H

#include "../../communicators/packet.h"

class resources_update: public packet {
	public:
		resources_update();
		resources_update(uint16_t tag, uint16_t critical_section_id, uint8_t* raw_resources, uint32_t raw_resources_size);

		uint16_t critical_section_id;
		uint8_t* raw_resources;
		uint32_t raw_resources_size;

		static uint32_t read_resources_size(uint8_t* raw_message);
	protected:	
		virtual void serialize_members(uint8_t* buf);
		virtual void deserialize_members(uint8_t* buf);
		virtual size_t calculate_members_size();
};

#endif
