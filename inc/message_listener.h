#ifndef MESSAGE_LISTENER_H
#define MESSAGE_LISTENER_H

#include "messages/frame.h"

class message_listener {
	public:
		virtual void on_message(frame*) = 0;
};

#endif
