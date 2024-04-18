#include <stdio.h>
#include <mpi.h>

#define N_VALUES 8

void my_send_int(void *buf, int count, int rank_to) {
	MPI_Send(buf, count, MPI_INT, rank_to, 0, MPI_COMM_WORLD);
}

void my_broadcast_send_int(void *buf, int count, int size) {
	for (int i = 1; i < size; ++i) {
		MPI_Send(buf, count, MPI_INT, i, 0, MPI_COMM_WORLD);
	}
}

void my_recv_int(void *buf, int count, int from) {
	MPI_Recv(buf, count, MPI_INT, from, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

void my_gather_recv_int(int *buf, int count, int rank_from, int rank_to) {
	for (int i = rank_from; i <= rank_to; ++i) {
		MPI_Recv(buf + i, count, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
}

///////

void print_arr(int arr[]) {
	printf("[%d", arr[0]);
	for (int i = 1; i < N_VALUES; ++i) {
		printf(", %d", arr[i]);
	}
	printf("]\n");
}

void print_arr_size(int arr[], int max) {
	printf("[%d", arr[0]);
	for (int i = 1; i < max; ++i) {
		printf(", %d", arr[i]);
	}
	printf("]\n");
}
