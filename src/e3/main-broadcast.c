// Personal Broadcast

#include <mpi.h>
#include "mycollective.c"

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0) {
		int values[] = {3, 7, 5, 10, 14, 9, 4, 2};

		for (int i = 1; i < size; ++i) {
			MPI_Send(&values, N_VALUES, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
		printf("master: ");
		print_arr(values);
	} else {
		int rec[N_VALUES];
		MPI_Recv(&rec, N_VALUES, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("slave:  ");
		print_arr(rec);
	}

	MPI_Finalize();
}
