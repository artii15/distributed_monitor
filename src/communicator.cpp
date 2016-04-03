#include "../inc/communicator.h"
#include "../inc/exceptions/invalid_message_exception.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

communicator::communicator(uint32_t process_id, unsigned int number_of_processes) {
	this->process_id = process_id;
	this->number_of_processes = number_of_processes;
	enabled = true;
}

void communicator::listen() {
	while(enabled) {
		receive_message();
	}
}

void communicator::handle(uint8_t* raw_message, uint16_t tag) {
	messages_handlers[tag]->handle(raw_message, tag);
/*
	switch(tag) {
		case MESSAGE_TAG::LOCK_REQUEST: {
			lock_request message;
			message.deserialize(raw_message);
			handle(&message);
			break;
		}
		case MESSAGE_TAG::LOCK_RESPONSE: {
			lock_response message;
			message.payload = &payload;
			message.deserialize(raw_message);
			handle(&message);
			break;
		}
		case MESSAGE_TAG::RELEASE_SIGNAL: {
			release_signal payload;
			message.payload = &payload;
			message.deserialize(raw_message);
			handle(&message);
			break;
		}
		case MESSAGE_TAG::WAIT_SIGNAL: {
			wait_signal payload;
			message.payload = &payload;
			message.deserialize(raw_message);
			handle(&message);
			break;
		}
		case MESSAGE_TAG::WAKE_SIGNAL: {
			wake_signal payload;
			message.payload = &payload;
			message.deserialize(raw_message);
			handle(&message);
			break;
		}
		default: throw invalid_message_exception("Not recognized message arrived");
	}
*/
}

communicator::~communicator() {}
