#ifndef LOCK_RESPONSE_H
#define LOCK_RESPONSE_H

#include "packet.h"
#include "lock_request.h"

class lock_response: public packet {
	public:
		lock_request confirmed_request;
		lock_request answer;

		lock_response();
		lock_response(const lock_request* confirmed_request, const lock_request* answer);

		virtual void serialize(uint8_t* buf);
		virtual void deserialize(uint8_t* serialized);
		virtual size_t get_size();

		virtual void be_handled_by(communicator*);

		virtual ~lock_response();
};

#endif
