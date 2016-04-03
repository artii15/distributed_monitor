#include "../inc/communicator.h"
#include "../inc/exceptions/invalid_message_exception.h"

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

void communicator::register_message_handler(uint16_t tag, message_handler* handler) {
	messages_handlers[tag] = handler;
}

void communicator::handle(uint8_t* raw_message, uint16_t tag) {
	map<uint16_t, message_handler*>::iterator handlers_iterator = messages_handlers.find(tag);
	if(handlers_iterator == messages_handlers.end()) {
		throw invalid_message_exception("Received message with unknown tag");
	}
	else {
		handlers_iterator->second->handle(raw_message, tag);
	}
}

communicator::~communicator() {}
