#ifndef SYNCHRONIZATION_REQUEST_MPI_TYPE
#define SYNCHRONIZATION_REQUEST_MPI_TYPE

#include <mpi.h>

class synchronization_request_mpi_type {
	public:
		synchronization_request_mpi_type();
		~synchronization_request_mpi_type();
		MPI_Datatype* get();

	private:
		MPI_Datatype type;
};

#endif
