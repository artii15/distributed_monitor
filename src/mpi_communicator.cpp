#include "../inc/mpi_communicator.h"
#include <mpi.h>
#include <stdlib.h>

using namespace std;

mpi_communicator::mpi_communicator(uint32_t process_id, unsigned int number_of_processes): communicator(process_id, number_of_processes) {}

void mpi_communicator::broadcast_message(frame* message) {
	size_t message_size = message->get_size();
	uint8_t serialized_message[message_size];
	message->serialize(serialized_message);

	for(unsigned int process_id = 0; process_id < number_of_processes; ++process_id) {
		if(process_id != this->process_id) {
			MPI_Send(serialized_message, message_size, MPI_BYTE, process_id, message->tag, MPI_COMM_WORLD);
		}
	}
}

frame* mpi_communicator::receive_message() {
	MPI_Status status;
	MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

	int message_size;
	MPI_Get_count(&status, MPI_BYTE, &message_size);
	uint8_t serialized_message[message_size];

	MPI_Recv(serialized_message, message_size, MPI_BYTE, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	return unpack(serialized_message, status.MPI_TAG);
}

frame* mpi_communicator::unpack(uint8_t* serialized_message, int tag) {
	frame* message = new frame();
	switch(tag) {
		case REQUEST_TAG::LOCK_REQUEST: message->payload = new sync_request(); break;
			
	}
	message->deserialize(serialized_message);

	return message;
}
