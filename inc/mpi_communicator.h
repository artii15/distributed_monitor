#ifndef MPI_COMMUNICATOR_H
#define MPI_COMMUNICATOR_H

#include "communicator.h"
#include "synchronization_request.h"

class mpi_communicator: public communicator {
	public:
		mpi_communicator(uint32_t rank, unsigned int number_of_processes);
		virtual void broadcast(synchronization_request*);
		virtual void listen();
	private:
		uint32_t time;
		uint32_t rank;
		unsigned int number_of_processes;
};

#endif
