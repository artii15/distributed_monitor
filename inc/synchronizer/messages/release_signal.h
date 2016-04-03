#ifndef RELEASE_SIGNAL_H
#define RELEASE_SIGNAL_H

#include "lock_request.h"

class release_signal: public synchronization_message {
	public:
		lock_request released_request;

		release_signal();
		release_signal(uint8_t* buf);
		release_signal(uint16_t tag, uint32_t time, const lock_request*);

		virtual ~release_signal();
	protected:
		virtual void serialize_synchronization_members(uint8_t* buf);
		virtual void deserialize_synchronization_members(uint8_t* buf);
		virtual size_t calculate_synchronization_members_size();
};

#endif
