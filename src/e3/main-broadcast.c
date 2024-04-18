// Personal Broadcast

#include <stdio.h>
#include "mycollective.c"

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0) {
		int values[] = {3, 7, 5, 10, 14, 9, 4, 2};

		my_broadcast_send_int(values, N_VALUES, size);

		printf("master: ");
		print_arr(values);
	} else {
		int rec[N_VALUES];

		my_recv_int(rec, N_VALUES, 0);

		printf("slave:  ");
		print_arr(rec);
	}

	MPI_Finalize();
}
