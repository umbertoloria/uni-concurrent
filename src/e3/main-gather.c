// Personal Gather

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include "mycollective.c"

#define STATIC_NUMBER 42

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0) {
		int *values = malloc(sizeof(int) * size);
		values[0] = STATIC_NUMBER;

		my_gather_recv_int(values, 1, 1, size-1);

		printf("master: ");
		print_arr_size(values, size);

		free(values);
	} else {
		int send = STATIC_NUMBER;

		my_send_int(&send, 1, 0);
	}

	MPI_Finalize();
}
