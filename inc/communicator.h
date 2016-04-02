#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "messages/packet.h"
#include "messages/lock_request.h"
#include "messages/lock_response.h"
#include "messages/release_signal.h"
#include "messages/wait_signal.h"
#include "messages/wake_signal.h"
#include "request_descriptor.h"
#include "monitor.h"
#include <pthread.h>
#include <map>
#include <set>

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
		communicator(uint32_t process_id, unsigned int number_of_processes);

		virtual void listen();
		virtual void broadcast_message(packet* message) = 0;
		virtual void send_message(packet* message, uint32_t recipient_id) = 0;

		virtual ~communicator();

	protected:
		virtual void receive_message(uint8_t** raw_message, uint16_t* tag) = 0;

		uint32_t process_id;
		unsigned int number_of_processes;

	private:
		void handle(uint8_t* raw_message, uint16_t tag);
		void handle(packet* message);
};

#endif
