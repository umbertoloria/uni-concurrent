#include <stdio.h>

#define N_VALUES 8

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
