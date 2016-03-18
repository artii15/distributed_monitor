#include "../inc/monitor.h"
#include <iostream>

using namespace std;

monitor::monitor(communicator* comm, int guarded_section_id) {
	this->comm = comm;
	this->guarded_section_id = guarded_section_id;
}

void monitor::call(action *action) {
	lock();
	action->perform(this);
	unlock();
}


void monitor::lock() {
	// Here id and rime should be readed from external object
	// synchronization_request lock_request(time, id);
	//comm->broadcast(&lock_request);
}

void monitor::unlock() {

}

void monitor::wait() {
		
}

void monitor::signal() {

}
