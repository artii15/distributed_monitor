#ifndef RELEASE_SIGNAL_H
#define RELEASE_SIGNAL_H

#include "lock_request.h"

class release_signal: public packet {
	public:
		lock_request released_request;

		release_signal();
		release_signal(const lock_request*);

		virtual ~release_signal();
	protected:
		virtual void serialize_members(uint8_t* buf);
		virtual void deserialize_members(uint8_t* buf);
		virtual size_t calculate_members_size();
};

#endif
