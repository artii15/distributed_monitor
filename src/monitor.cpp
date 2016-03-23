#include "../inc/monitor.h"
#include <pthread.h>
#include <iostream>

using namespace std;

monitor::monitor(communicator* comm, uint16_t critical_section_id) {
	this->comm = comm;
	this->critical_section_id = critical_section_id;
}

void monitor::call(action *action) {
	lock();
	action->perform(this);
	unlock();
}

void monitor::call(void (*callback)(monitor*)) {
	lock();
	callback(this);
	unlock();
}

void monitor::lock() {
	pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	
	comm->send_lock_request(critical_section_id, &mutex);

	pthread_mutex_lock(&mutex);
	pthread_mutex_unlock(&mutex);

	pthread_mutex_destroy(&mutex);
}

void monitor::unlock() {
	comm->send_release_signal(critical_section_id);
}

void monitor::wait() {
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);

	comm->send_wait_signal(critical_section_id, &mutex);

	pthread_mutex_lock(&mutex);
	pthread_mutex_unlock(&mutex);

	pthread_mutex_destroy(&mutex);
}

void monitor::signal() {
	comm->send_wake_signal(critical_section_id);
}
