#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <stdint.h>

class message_handler {
	public:
		virtual void handle(uint8_t* raw_message, uint16_t tag) = 0;
};

#endif
