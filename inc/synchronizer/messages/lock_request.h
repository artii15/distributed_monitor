#ifndef LOCK_REQUEST_H
#define LOCK_REQUEST_H

#include "synchronization_message.h"

class lock_request: public synchronization_message {
	public:
		uint32_t process_id;
		uint16_t critical_section_id;

		lock_request();
		lock_request(uint8_t* buf);
		lock_request(uint16_t tag, uint32_t time, uint32_t process_id, uint16_t critical_section_id);

		bool operator>(const lock_request& request) const;
		bool operator==(const lock_request& request) const;
		bool operator<(const lock_request& request) const;

		virtual ~lock_request();
	protected:
		virtual void serialize_synchronization_members(uint8_t* buf);
		virtual void deserialize_synchronization_members(uint8_t* buf);
		virtual size_t calculate_synchronization_members_size();
};

#endif
