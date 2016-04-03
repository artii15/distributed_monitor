#ifndef LOCK_REQUEST_H
#define LOCK_REQUEST_H

#include "../../communicators/packet.h"

class lock_request: public packet {
	public:
		uint32_t process_id;
		uint32_t creation_time;
		uint16_t critical_section_id;

		lock_request();
		lock_request(uint8_t* buf);
		lock_request(uint32_t process_id, uint32_t creation_time, uint16_t critical_section_id);

		bool operator>(const lock_request& request) const;
		bool operator==(const lock_request& request) const;
		bool operator<(const lock_request& request) const;

		virtual ~lock_request();
	protected:
		virtual void serialize_members(uint8_t* buf);
		virtual void deserialize_members(uint8_t* buf);
		virtual size_t calculate_members_size();
};

#endif
