#ifndef SYNC_REQUEST_H
#define SYNC_REQUEST_H

#include "serializable.h"

class sync_request: public serializable {
	public:
		uint32_t process_id;
		uint32_t creation_time;
		uint16_t critical_section_id;

		sync_request();
		sync_request(uint32_t process_id, uint32_t creation_time, uint16_t critical_section_id);

		bool operator>(const sync_request& request) const;
		bool operator==(const sync_request& request) const;
		bool operator<(const sync_request& request) const;

		void serialize(uint8_t* buf);
		void deserialize(uint8_t* serialized);
		size_t get_size();
};

#endif