#ifndef MPI_COMMUNICATOR_H
#define MPI_COMMUNICATOR_H

#include "communicator.h"
#include "synchronization_request.h"

class mpi_communicator: public communicator {
	public:
		virtual void listen();

	protected:
		virtual void broadcast_sync_request(synchronization_request*);

	private:
		unsigned int number_of_processes;

		void handle_request(synchronization_request*);
		void handle_lock_request(synchronization_request*);
};

#endif
