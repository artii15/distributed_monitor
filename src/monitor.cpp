#include "../inc/monitor.h"
#include <pthread.h>
#include <iostream>

using namespace std;

monitor::monitor(communicator* comm, uint16_t critical_section_id) {
	this->comm = comm;
	this->critical_section_id = critical_section_id;
}

void monitor::call(action *action) {
	lock_request sent_request = lock();
	action->perform(this);
	unlock(&sent_request);
}

void monitor::call(void (*callback)(monitor*)) {
	lock_request sent_request = lock();
	callback(this);
	unlock(&sent_request);
}

lock_request monitor::lock() {
	pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	
	lock_request sent_request = comm->send_lock_request(critical_section_id, &mutex);

	pthread_mutex_lock(&mutex);
	pthread_mutex_unlock(&mutex);

	pthread_mutex_destroy(&mutex);

	return sent_request;
}

void monitor::unlock(lock_request* sent_request) {
	comm->send_release_signal(sent_request);
}

void monitor::wait() {
	
}

void monitor::signal() {

}
