#ifndef MPI_COMMUNICATOR_H
#define MPI_COMMUNICATOR_H

#include "communicator.h"
#include "synchronization_request.h"

class mpi_communicator: public communicator {
	public:
		mpi_communicator(uint32_t process_id, unsigned int number_of_processes);
		virtual void listen();
	protected:
		virtual void broadcastSyncRequest(uint16_t guarded_section_id, request_tag tag);
	private:
		uint32_t time;
		uint32_t process_id;
		unsigned int number_of_processes;

		void handle_request(synchronization_request*);
		void handle_lock_request(synchronization_request*);
};

#endif
