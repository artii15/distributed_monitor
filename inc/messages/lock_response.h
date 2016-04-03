#ifndef LOCK_RESPONSE_H
#define LOCK_RESPONSE_H

#include "packet.h"
#include "lock_request.h"

class lock_response: public packet {
	public:
		lock_request confirmed_request;
		lock_request answer;

		lock_response();
		lock_response(uint16_t tag, uint32_t time, const lock_request* confirmed_request, const lock_request* answer);

		virtual ~lock_response();
	protected:
		virtual void serialize_members(uint8_t* buf);
		virtual void deserialize_members(uint8_t* buf);
		virtual size_t calculate_members_size();
};

#endif
