#ifndef LOCK_REQUEST_H
#define LOCK_REQUEST_H

#include "packet.h"

class lock_request: public packet {
	public:
		uint32_t process_id;
		uint32_t creation_time;
		uint16_t critical_section_id;

		lock_request();
		lock_request(uint32_t process_id, uint32_t creation_time, uint16_t critical_section_id);

		bool operator>(const lock_request& request) const;
		bool operator==(const lock_request& request) const;
		bool operator<(const lock_request& request) const;

		virtual ~lock_request();
	protected:
		virtual size_t calculate_size();
		virtual void pack_into_buffer(uint8_t* buf);
		virtual void unpack_from_buffer(uint8_t* buf);

};

#endif
