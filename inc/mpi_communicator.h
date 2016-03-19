#ifndef MPI_COMMUNICATOR_H
#define MPI_COMMUNICATOR_H

#include "communicator.h"
#include "messages/frame.h"

class mpi_communicator: public communicator {
	public:
		mpi_communicator(uint32_t process_id, unsigned int number_of_processes);

	protected:
		virtual void broadcast_message(frame* message);
		virtual void receive_message(frame* message);
};

#endif
