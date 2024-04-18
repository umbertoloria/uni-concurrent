// Personal Gather

#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define STATIC_NUMBER 42

void print_arr(int arr[], int max) {
	printf("[%d", arr[0]);
	for (int i = 1; i < max; ++i) {
		printf(", %d", arr[i]);
	}
	printf("]\n");
}

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0) {
		int *values = malloc(sizeof(int) * size);
		values[0] = STATIC_NUMBER;
		for (int i = 1; i < size; ++i) {
			MPI_Recv(&values[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
		printf("master: ");
		print_arr(values, size);
		free(values);

	} else {
		int send = STATIC_NUMBER;
		MPI_Send(&send, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
}
