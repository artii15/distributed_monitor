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
}

communicator::~communicator() {}
