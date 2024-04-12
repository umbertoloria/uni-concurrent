// Sending and receiving strings

#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (rank == 0) {
		printf("Give me a string> ");
		fflush(stdout);
		char tosend[100];
		scanf("%s", tosend);
		MPI_Send(tosend, strlen(tosend)+1, MPI_CHAR, 1, 1, MPI_COMM_WORLD);

		char torecv[100];
		MPI_Recv(torecv, 100, MPI_CHAR, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Received> %s\n", torecv);
	} else {
		char torecv[100];
		MPI_Recv(torecv, 100, MPI_CHAR, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		torecv[1] = '.';
		MPI_Send(torecv, strlen(torecv)+1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
		printf("Sent> %s\n", torecv);
	}

	MPI_Finalize();
}
