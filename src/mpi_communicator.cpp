#include "../inc/mpi_communicator.h"
#include <mpi.h>

using namespace std;

mpi_communicator::mpi_communicator(const environment_descriptor* env, MPI_Comm* mpi_comm): communicator(env) {
	this->mpi_comm = *mpi_comm;
}

void mpi_communicator::broadcast_message(packet* message) {
	size_t message_size = message->get_size();
	uint8_t serialized_message[message_size];
	message->serialize(serialized_message);

	for(unsigned int process_id = 0; process_id < env->number_of_processes; ++process_id) {
		if(process_id != env->process_id) {
			MPI_Send(serialized_message, message_size, MPI_BYTE, process_id, message->tag, mpi_comm);
		}
	}
}

void mpi_communicator::send_message(packet* message, uint32_t recipient_id) {
	size_t message_size = message->get_size();
	uint8_t serialized_message[message_size];
	message->serialize(serialized_message);

	MPI_Send(serialized_message, message_size, MPI_BYTE, recipient_id, message->tag, mpi_comm);
}

void mpi_communicator::receive_message() {
	MPI_Status status;
	MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, mpi_comm, &status);

	int message_size;
	MPI_Get_count(&status, MPI_BYTE, &message_size);

	uint8_t raw_message[message_size];
	MPI_Recv(raw_message, message_size, MPI_BYTE, status.MPI_SOURCE, status.MPI_TAG, mpi_comm, MPI_STATUS_IGNORE);

	handle(raw_message, status.MPI_TAG);
}
