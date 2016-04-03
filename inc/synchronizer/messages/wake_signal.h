#ifndef WAKE_SIGNAL_H
#define WAKE_SIGNAL_H

#include "wait_signal.h"

class wake_signal: public synchronization_message {
	public:
		wait_signal signal_to_release;

		wake_signal();
		wake_signal(uint8_t* buf);
		wake_signal(uint16_t tag, uint32_t time, const wait_signal*);

		virtual ~wake_signal();
	protected:
		virtual void serialize_synchronization_members(uint8_t* buf);
		virtual void deserialize_synchronization_members(uint8_t* buf);
		virtual size_t calculate_synchronization_members_size();
};

#endif
