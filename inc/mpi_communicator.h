#ifndef MPI_COMMUNICATOR_H
#define MPI_COMMUNICATOR_H

#include "communicator.h"
#include "synchronization.h"

class mpi_communicator: public communicator {
	public:
		mpi_communicator(int rank, int number_of_processes);
		virtual void broadcast(synchronization_request*);
		virtual void Ibroadcast(synchronization_request*);
		virtual void listen();
	private:
		int rank;
		int number_of_processes;
		timestamp time;
};

#endif
