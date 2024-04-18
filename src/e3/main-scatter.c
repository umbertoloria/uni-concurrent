// Personal Scatter

#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "mycollective.c"

#define N_VALUES 8
#define STATIC_NUMBER 42

int myceil(float num) {
	int int_num = (int) num;
	return (num - int_num) > 0 ? int_num + 1 : int_num;
}

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int size_ch = size - 1; // Only childs.
	int elems_per_process = myceil(N_VALUES / (float) size_ch);
	if (elems_per_process < 1) {
		elems_per_process = 1;
	}
	int elems_last_process = N_VALUES - ((size_ch - 1) * elems_per_process);
	if (elems_last_process < 0) {
		elems_last_process = 0;
	}
	int last_rank = N_VALUES / elems_per_process + (elems_last_process > 0 ? 1 : 0);

	if (rank == 0) {

		/* printf("ELEM PER PROCESS: %d\n", elems_per_process);
		printf("ELEM LAST PROCESS: %d\n", elems_last_process);
		printf("LAST RANK: %d\n\n", last_rank); */

		int values[] = {1, 2, 3, 4, 5, 6, 7, 8};

		int i = 1;
		int offset = 0;
		while (i < size - 1 && offset < N_VALUES) {
			MPI_Send(&values[offset], elems_per_process, MPI_INT, i, 0, MPI_COMM_WORLD);
			offset += elems_per_process;
			++i;
		}
		if (offset < N_VALUES) {
			MPI_Send(&values[offset], elems_last_process, MPI_INT, i, 0, MPI_COMM_WORLD);
		}

	} else {

		int my_size = rank == size-1 ? elems_last_process : elems_per_process;

		if (last_rank < rank) {

			printf("slave %d without work\n", rank);

		} else if (my_size > 0) {

			int *rec = malloc(sizeof(int) * my_size);

			MPI_Recv(rec, my_size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			printf("slave %d received: ", rank);
			print_arr_size(rec, my_size);

			free(rec);

		} else {

			// Never happens.
			printf("slave %d without work\n", rank);

		}

	}

	MPI_Finalize();
}
