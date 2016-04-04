#include "../inc/monitor.h"
#include <pthread.h>

using namespace std;

monitor::monitor(synchronizer* proc_synchronizer, resources_synchronizer* res_synchronizer, uint16_t critical_section_id) {
	this->proc_synchronizer = proc_synchronizer;
	this->res_synchronizer = res_synchronizer;
	this->critical_section_id = critical_section_id;
}

void monitor::call(action *action) {
	lock();

	action->perform(this);

	res_synchronizer->update(critical_section_id);
	unlock();
}

void monitor::call(void (*callback)(monitor*)) {
	lock();

	callback(this);

	res_synchronizer->update(critical_section_id);
	unlock();
}

void monitor::lock() {
	pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	
	proc_synchronizer->lock_section(critical_section_id, &mutex);

	pthread_mutex_lock(&mutex);
	pthread_mutex_unlock(&mutex);

	pthread_mutex_destroy(&mutex);
}

void monitor::unlock() {
	proc_synchronizer->release_section(critical_section_id);
}

void monitor::wait() {
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);

	proc_synchronizer->wait_in_section(critical_section_id, &mutex);

	pthread_mutex_lock(&mutex);
	pthread_mutex_unlock(&mutex);

	pthread_mutex_destroy(&mutex);
}

void monitor::notify() {
	proc_synchronizer->wake_one_in_section(critical_section_id);
}

void monitor::notify_all() {
	proc_synchronizer->wake_all_in_section(critical_section_id);
}
