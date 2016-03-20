#ifndef MPI_COMMUNICATOR_H
#define MPI_COMMUNICATOR_H

#include "communicator.h"
#include "messages/frame.h"
#include <mpi.h>

class mpi_communicator: public communicator {
	public:
		mpi_communicator(uint32_t process_id, unsigned int number_of_processes, MPI_Comm* mpi_comm);

	protected:
		virtual void broadcast_message(frame* message);
		virtual void send_message(frame* message, uint32_t recipient_id);
		virtual frame* receive_message();

	private:
		MPI_Comm mpi_comm;
		frame* unpack(uint8_t* serialized_message, int tag);
};

#endif
