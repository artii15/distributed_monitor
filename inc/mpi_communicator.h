#ifndef MPI_COMMUNICATOR_H
#define MPI_COMMUNICATOR_H

#include "communicator.h"
#include "messages/packet.h"
#include <mpi.h>

class mpi_communicator: public communicator {
	public:
		mpi_communicator(const environment_descriptor* env, MPI_Comm* mpi_comm);

	protected:
		virtual void broadcast_message(packet* message);
		virtual void send_message(packet* message, uint32_t recipient_id);
		virtual void receive_message();

	private:
		MPI_Comm mpi_comm;
};

#endif
