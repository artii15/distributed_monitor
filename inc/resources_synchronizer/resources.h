#ifndef RESOURCES_H
#define RESOURCES_H

#include "../serializable.h"

class resources: public serializable {
	public:
		uint32_t version;
		uint16_t critical_section_id;
		bool is_dirty;

		resources(uint16_t critical_section_id, uint32_t version);

		void update(uint8_t* raw_resource);

		virtual void serialize(uint8_t* buf);
		virtual void deserialize(uint8_t* buf);
		virtual size_t get_size();

	protected:
		virtual void serialize_resources_members(uint8_t* buf) = 0;
		virtual void deserialize_resources_members(uint8_t* buf) = 0;
		virtual size_t calculate_resources_members_size() = 0;
};

#endif
