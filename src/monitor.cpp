#include "../inc/monitor.h"
#include <iostream>

using namespace std;

void monitor::call(action *action) {
	lock();
	action->perform(this);
	unlock();
}


void monitor::lock() {
	for(list<process_id>::iterator it = processes_ids.begin(); it != processes_ids.end(); ++it) {
		cout << ' ' << *it;
	}
	cout << endl;
}

void monitor::unlock() {

}

void monitor::wait() {
		
}

void monitor::signal() {

}

void monitor::register_process(process_id id) {
	processes_ids.push_back(id);
}
