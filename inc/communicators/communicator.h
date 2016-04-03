#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "packet.h"
#include "message_handler.h"
#include "../environment_descriptor.h"
#include <map>

typedef struct MESSAGE_TAG {
	const static uint16_t LOCK_REQUEST = 1;
	const static uint16_t LOCK_RESPONSE = 2;
	const static uint16_t RELEASE_SIGNAL = 3;
	const static uint16_t WAIT_SIGNAL = 4;
	const static uint16_t WAKE_SIGNAL = 5;
} MESSAGE_TAG;

class communicator {
	public:
		bool enabled;
		communicator(const environment_descriptor* env);

		virtual void listen();
		virtual void broadcast_message(packet* message) = 0;
		virtual void send_message(packet* message, uint32_t recipient_id) = 0;

		void register_message_handler(uint16_t tag, message_handler* handler);

		virtual ~communicator();

	protected:
		virtual void receive_message() = 0;
		void handle(uint8_t* raw_message, uint16_t tag);

		const environment_descriptor* env;
	private:
		std::map<uint16_t, message_handler*> messages_handlers;
};

#endif
