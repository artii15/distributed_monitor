#ifndef RESOURCES_UPDATE_H
#define RESOURCES_UPDATE_H

#include "../../communicators/packet.h"
#include "../../resources_synchronizer/resources.h"

class resources_update: public packet {
	public:
		resources_update();
		resources_update(uint16_t tag, uint16_t critical_section_id, resources* res);

		uint16_t critical_section_id;
		resources* res;
	protected:	
		virtual void serialize_members(uint8_t* buf);
		virtual void deserialize_members(uint8_t* buf);
		virtual size_t calculate_members_size();
};

#endif
