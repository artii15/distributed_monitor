struct synchronization_request {
	unsigned long time;
	unsigned long process_id;

	synchronization_request(unsigned long time, unsigned long process_id) {
		this->time = time;
		this->process_id = process_id;
	}

	bool operator>(const synchronization_request& request) const {
		return time > request.time || (time == request.time && process_id > request.process_id);
	}

	bool operator==(const synchronization_request& request) const {
		return time == request.time && process_id == request.process_id;
	}

	bool operator<(const synchronization_request& request) const {
		return !(*this == request || *this > request);
	}
};
