#ifndef PRODUCER_ACTION_H
#define PRODUCER_ACTION_H

#include "../action.h"
#include "buffer.hpp"

class producer_action: public action {
	public:
		producer_action(buffer*, uint32_t producer_id);

		virtual void perform(monitor*);
	private:
		buffer* buf;
		uint32_t producer_id;
};

#endif
