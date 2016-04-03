#ifndef WAIT_SIGNAL_H
#define WAIT_SIGNAL_H

#include "lock_request.h"

class wait_signal: public synchronization_message {
	public:
		lock_request request_to_remove;

		wait_signal();
		wait_signal(uint8_t* buf);
		wait_signal(uint16_t tag, uint32_t time, const lock_request*);

		bool operator>(const wait_signal& signal) const;
		bool operator==(const wait_signal& signal) const;
		bool operator<(const wait_signal& signal) const;

		virtual ~wait_signal();
	protected:
		virtual void serialize_synchronization_members(uint8_t* buf);
		virtual void deserialize_synchronization_members(uint8_t* buf);
		virtual size_t calculate_synchronization_members_size();
};

#endif
