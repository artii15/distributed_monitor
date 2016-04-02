#ifndef MESSAGE_LISTENER_H
#define MESSAGE_LISTENER_H

#include "messages/packet.h"

class message_listener {
	public:
		virtual void on_message(packet*) = 0;
};

#endif
