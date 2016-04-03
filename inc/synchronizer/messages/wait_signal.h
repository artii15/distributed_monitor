#ifndef WAIT_SIGNAL_H
#define WAIT_SIGNAL_H

#include "lock_request.h"
#include "../../communicators/packet.h"

class wait_signal: public packet {
	public:
		lock_request request_to_remove;

		wait_signal();
		wait_signal(uint8_t* buf);
		wait_signal(const lock_request*);

		bool operator>(const wait_signal& signal) const;
		bool operator==(const wait_signal& signal) const;
		bool operator<(const wait_signal& signal) const;

		virtual ~wait_signal();
	protected:
		virtual void serialize_members(uint8_t* buf);
		virtual void deserialize_members(uint8_t* buf);
		virtual size_t calculate_members_size();
};

#endif
