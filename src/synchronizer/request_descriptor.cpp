#include "../../inc/synchronizer/request_descriptor.h"

request_descriptor::request_descriptor() {
	this->mutex = NULL;
	this->number_of_confirmations = 0;
}

request_descriptor::request_descriptor(pthread_mutex_t* mutex, unsigned int number_of_confirmations) {
	this->mutex = mutex;
	this->number_of_confirmations = number_of_confirmations;
}
