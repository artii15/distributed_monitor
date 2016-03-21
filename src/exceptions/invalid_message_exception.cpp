#include "../../inc/exceptions/invalid_message_exception.h"

invalid_message_exception::invalid_message_exception(const char* message) {
	this->message = message;
}

const char* invalid_message_exception::what() const throw() {
	return message;
}
