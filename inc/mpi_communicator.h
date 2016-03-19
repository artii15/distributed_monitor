#ifndef MPI_COMMUNICATOR_H
#define MPI_COMMUNICATOR_H

#include "communicator.h"
#include "synchronization_request.h"

class mpi_communicator: public communicator {
	public:
		mpi_communicator(uint32_t process_id, unsigned int number_of_processes);

	protected:
		virtual void broadcast_sync_request(synchronization_request*);
		virtual void receive_message(synchronization_request* message);
};

#endif
