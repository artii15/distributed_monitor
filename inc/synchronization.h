#ifndef SYNCHRONIZATION_H
#define SYNCHRONIZATION_H

typedef int process_id;
typedef unsigned long long timestamp;

struct synchronization_request {
	timestamp time;
	process_id pid;

	synchronization_request(timestamp time, process_id pid) {
		this->time = time;
		this->pid = pid;
	}

	bool operator>(const synchronization_request& request) const {
		return time > request.time || (time == request.time && pid > request.pid);
	}

	bool operator==(const synchronization_request& request) const {
		return time == request.time && pid == request.pid;
	}

	bool operator<(const synchronization_request& request) const {
		return !(*this == request || *this > request);
	}
};

#endif
