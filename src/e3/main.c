// Broadcast

#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define N_VALUES 8

void print_arr(int arr[]) {
	printf("[%d", arr[0]);
	for (int i = 1; i < N_VALUES; ++i) {
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
		printf("master broadcasts numbers to all slaves\n");
		int values[] = {3, 7, 5, 10, 14, 9, 4, 2};
		MPI_Bcast(&values, N_VALUES, MPI_INT, 0, MPI_COMM_WORLD);

		int i = 1;
		int prev_sum;
		MPI_Recv(&prev_sum, 1, MPI_INT, i++, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		int ok = 1;
		for (; i < size; ++i) {
			int cur_sum;
			MPI_Recv(&cur_sum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if (prev_sum != cur_sum) {
				printf("wrong sum for rank=%d (given=%d, oracle=%d)\n", i-1, cur_sum, prev_sum);
				ok = 0;
			}
		}

		if (ok) {
			printf("CORRECT, all processes gave %d\n", prev_sum);
		}
	} else {
		int rec[N_VALUES];
		MPI_Bcast(&rec, N_VALUES, MPI_INT, 0, MPI_COMM_WORLD);

		int sum = 0;
		for (int i = 0; i < N_VALUES; ++i) {
			sum += rec[i];
		}

		MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
}
