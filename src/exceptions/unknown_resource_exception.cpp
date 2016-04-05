#include "../../inc/exceptions/unknown_resource_exception.h"

unknown_resource_exception::unknown_resource_exception(const char* message) {
	this->message = message;
}

const char* unknown_resource_exception::what() const throw() {
	return message;
}
