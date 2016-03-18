#include "../inc/pending_request.h"

pending_request::pending_request(synchronization_request* request, pthread_mutex_t* mutex, unsigned int number_of_confirmations) {
	this->request = request;
	this->mutex = mutex;
	this->number_of_confirmations = number_of_confirmations;
}

bool pending_request::operator>(const pending_request& pending) const {
	return *request > *pending.request;
}
