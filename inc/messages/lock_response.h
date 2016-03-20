#ifndef LOCK_RESPONSE_H
#define LOCK_RESPONSE_H

#include "packet.h"
#include "lock_request.h"

class lock_response: public packet {
	public:
		lock_request confirmed_request;
		lock_request top_request;

		lock_response();
		lock_response(lock_request* confirmed_request, lock_request* top_request);

		void serialize(uint8_t* buf);
		void deserialize(uint8_t* serialized);
		size_t get_size();

		virtual void be_handled_by(communicator*);

		virtual ~lock_response();
};

#endif
