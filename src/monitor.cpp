#include "../inc/monitor.h"
#include <pthread.h>
#include <iostream>

using namespace std;

monitor::monitor(communicator* comm, uint16_t guarded_section_id) {
	this->comm = comm;
	this->guarded_section_id = guarded_section_id;
}

void monitor::call(action *action) {
	lock();
	action->perform(this);
	unlock();
}


void monitor::lock() {
	pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	
	comm->sendLockRequest(guarded_section_id, &mutex);

	pthread_mutex_lock(&mutex);
	pthread_mutex_unlock(&mutex);

	pthread_mutex_destroy(&mutex);
}

void monitor::unlock() {

}

void monitor::wait() {
	
}

void monitor::signal() {

}
