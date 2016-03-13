#include "../inc/monitor.h"

void monitor::call(action *action) {
	lock();
	action->perform(this);
	unlock();
}


void monitor::lock() {
	
}

void monitor::unlock() {

}

void monitor::wait() {
		
}

void monitor::signal() {

}
