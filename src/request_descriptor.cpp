#include "../inc/request_descriptor.h"

request_descriptor::request_descriptor(synchronization_request* request, pthread_mutex_t* mutex, unsigned int number_of_confirmations) {
	this->request = request;
	this->mutex = mutex;
	this->number_of_confirmations = number_of_confirmations;
}

bool request_descriptor::operator>(const request_descriptor& descriptor) const {
	return *request > *descriptor.request;
}
