#ifndef MPI_COMMUNICATOR_H
#define MPI_COMMUNICATOR_H

#include "communicator.h"
#include "messages/packet.h"
#include <mpi.h>

class mpi_communicator: public communicator {
	public:
		mpi_communicator(uint32_t process_id, unsigned int number_of_processes, MPI_Comm* mpi_comm);

	protected:
		virtual void broadcast_message(packet* message);
		virtual void send_message(packet* message, uint32_t recipient_id);
		virtual void receive_message(uint8_t** raw_message, uint16_t* tag);

	private:
		MPI_Comm mpi_comm;
};

#endif
