// Barriers

#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int rand_sec() {
	int r = rand();
	float rr = (r % 100) / 100.0f;
	int max_sec = 5; // Max 5 seconds, 5 excluded.
	return (int) (rr * max_sec);
}

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	srand(time(NULL) + rank);

	if (rank == 0) {
		printf("master waits all slaves\n");
	} else {
		int waiting = rand_sec();
		printf("slave %d waits %ds\n", rank, waiting);
		sleep(waiting);
	}

	MPI_Barrier(MPI_COMM_WORLD);

	if (rank == 0) {
		printf("master after barrier\n");
	}

	MPI_Finalize();
}
