#include "../inc/mpi_communicator.h"
#include "../inc/exceptions/invalid_message_exception.h"
#include <mpi.h>
#include <stdlib.h>

using namespace std;

mpi_communicator::mpi_communicator(uint32_t process_id, unsigned int number_of_processes, MPI_Comm* mpi_comm): communicator(process_id, number_of_processes) {
	this->mpi_comm = *mpi_comm;
}

void mpi_communicator::broadcast_message(frame* message) {
	size_t message_size = message->get_size();
	uint8_t serialized_message[message_size];
	message->serialize(serialized_message);

	for(unsigned int process_id = 0; process_id < number_of_processes; ++process_id) {
		if(process_id != this->process_id) {
			MPI_Send(serialized_message, message_size, MPI_BYTE, process_id, message->tag, mpi_comm);
		}
	}
}

void mpi_communicator::send_message(frame* message, uint32_t recipient_id) {
	size_t message_size = message->get_size();
	uint8_t serialized_message[message_size];
	message->serialize(serialized_message);

	MPI_Send(serialized_message, message_size, MPI_BYTE, recipient_id, message->tag, mpi_comm);
}

frame* mpi_communicator::receive_message() {
	MPI_Status status;
	MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, mpi_comm, &status);

	int message_size;
	MPI_Get_count(&status, MPI_BYTE, &message_size);
	uint8_t serialized_message[message_size];

	MPI_Recv(serialized_message, message_size, MPI_BYTE, status.MPI_SOURCE, status.MPI_TAG, mpi_comm, MPI_STATUS_IGNORE);

	return unpack(serialized_message, status.MPI_TAG);
}

frame* mpi_communicator::unpack(uint8_t* serialized_message, int tag) {
	frame* message = new frame();
	switch(tag) {
		case MESSAGE_TAG::LOCK_REQUEST: message->payload = new lock_request(); break;
		case MESSAGE_TAG::LOCK_RESPONSE: message->payload = new lock_response(); break;
		case MESSAGE_TAG::RELEASE_SIGNAL: message->payload = new release_signal(); break;
		case MESSAGE_TAG::WAIT_SIGNAL: message->payload = new wait_signal(); break;
		default: throw invalid_message_exception("Not recognized message arrived");
			
	}
	message->deserialize(serialized_message);

	return message;
}
