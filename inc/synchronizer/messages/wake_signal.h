#ifndef WAKE_SIGNAL_H
#define WAKE_SIGNAL_H

#include "wait_signal.h"
#include "../../communicators/packet.h"

class wake_signal: public packet {
	public:
		wait_signal signal_to_release;

		wake_signal();
		wake_signal(uint8_t* buf);
		wake_signal(const wait_signal*);

		virtual ~wake_signal();
	protected:
		virtual void serialize_members(uint8_t* buf);
		virtual void deserialize_members(uint8_t* buf);
		virtual size_t calculate_members_size();
};

#endif
