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
		virtual size_t calculate_size();
		virtual void pack_into_buffer(uint8_t* buf);
		virtual void unpack_from_buffer(uint8_t* buf);
};

#endif
