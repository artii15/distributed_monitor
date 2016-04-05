#ifndef CONSUMER_ACTION_H
#define CONSUMER_ACTION_H

#include "../action.h"
#include "buffer.hpp"

class consumer_action: public action {
	public:
		consumer_action(buffer*);

		virtual void perform(monitor*);
	private:
		buffer* buf;
};

#endif
