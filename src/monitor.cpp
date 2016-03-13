#include "../inc/monitor.h"
#include <iostream>

using namespace std;

monitor::monitor(process_id id) {
	time = 0;
	this->id = id;
	register_process(id);
}

void monitor::call(action *action) {
	lock();
	action->perform(this);
	unlock();
}


void monitor::lock() {
	synchronization_request lock_request(time, id);
	for(set<process_id>::iterator it = processes_ids.begin(); it != processes_ids.end(); ++it) {
		comm->send(&lock_request, *it);
	}
}

void monitor::unlock() {

}

void monitor::wait() {
		
}

void monitor::signal() {

}

void monitor::register_process(process_id id) {
	processes_ids.insert(id);
}
