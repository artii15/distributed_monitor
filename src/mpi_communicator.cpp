#include "../inc/mpi_communicator.h"
#include <mpi.h>

mpi_communicator::mpi_communicator(int rank, int number_of_processes) {
	this->rank = rank;
	this->number_of_processes = number_of_processes;
	time = 0;

}

void mpi_communicator::broadcast() {
	for()					
}

void mpi_communicator::Ibroadcast() {
}
