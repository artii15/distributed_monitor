#include "../inc/monitor.h"
#include <pthread.h>
#include <iostream>

using namespace std;

monitor::monitor(synchronizer* synchronizator, uint16_t critical_section_id) {
	this->synchronizator = synchronizator;
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
	
	//comm->send_lock_request(critical_section_id, &mutex);

	pthread_mutex_lock(&mutex);
	pthread_mutex_unlock(&mutex);

	pthread_mutex_destroy(&mutex);
}

void monitor::unlock() {
	synchronizator->release_section(critical_section_id);
}

void monitor::wait() {
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);

	synchronizator->wait_in_section(critical_section_id, &mutex);

	pthread_mutex_lock(&mutex);
	pthread_mutex_unlock(&mutex);

	pthread_mutex_destroy(&mutex);
}

void monitor::notify() {
	synchronizator->wake_one_in_section(critical_section_id);
}

void monitor::notify_all() {
	synchronizator->wake_all_in_section(critical_section_id);
}
