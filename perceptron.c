#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "perceptron.h"

static int calc_check(int *x_vec, int *beta_vec, int *target) {
	return *target * (beta_vec[0] + beta_vec[1] * x_vec[0] + beta_vec[2] * x_vec[1]);
}

static void update_hyperplane(int *x_vec, int *beta_vec, int *target) {
	size_t beta_vec_size = sizeof(beta_vec) / sizeof(beta_vec[0]) + 1;
	printf("%s: beta_vec_size: %zu\n", __func__, beta_vec_size);

	beta_vec[0] = beta_vec[0] + ALPHA * *target;
	for (size_t i = 1; i < beta_vec_size; i++) {
		beta_vec[i] = beta_vec[i] + ALPHA * *target * x_vec[i-1];
	}
}

int main(int argc, char **argv) {
	int data_set[MATRIX_ROWS][MATRIX_COLS];
	int beta_vec[1][MATRIX_COLS];
	const int data_set_size = sizeof(data_set) / sizeof(data_set[0]);
	const int beta_vec_size = sizeof(beta_vec) / sizeof(beta_vec[0]);
	time_t time;
	data_set_entry *data_ptr = data_set;

	// TEST!
	parseData(data_set, "x_data", "data.txt");
	parseData(beta_vec, "beta_data", "data.txt");

	int errors = 0;
	int steps_performed = 0;
	int num_updates = 0;
	time = clock(); // start time
	do {
		errors = 0;
		for (int i = 0; i < beta_vec_size; i++) {
			printf("[%d][*] beta_vec: (%d, %d, %d)\n", steps_performed, beta_vec[i][0],
					beta_vec[i][1], beta_vec[i][2]);
		}
		for (int i = 0; i < data_set_size; i++) {
			int *x_vec = data_ptr[i];
			int target = data_ptr[i][MATRIX_COLS-1];

			printf("[%d][%d] data_set_vec: (%d, %d, %d)\n", steps_performed, i, data_ptr[i][0],
					data_ptr[i][1], target);

			int result = calc_check(data_ptr[i], beta_vec[0], &target);
#ifdef VERBOSE
			printf("[%d][%d] result: %d\n", steps_performed, i, result);
#endif

			if (result <= 0) {
				errors++;
				num_updates++;
				printf("[%d][%d] errors++, updating the hyperplane!\n", steps_performed, i);
				update_hyperplane(x_vec, beta_vec[0], &target);
			}
		}
		steps_performed++;
		// safety check
		if (steps_performed > 20) {
			printf("20 steps performed, bailing out...\n");
			break;
		}
	} while (errors > 0);

	time = clock() - time; // end time
	double time_taken = ((double)time) / CLOCKS_PER_SEC; // in seconds
	time_taken *= 1000; // millisecs

	printf("FINAL HYPERPLANE: %d + %d * x1 + %d * x2\n", beta_vec[0][0], beta_vec[0][1], beta_vec[0][2]);
	printf("TOTAL num of updates: %d\n", num_updates);
	printf("TOTAL execution time: %f msecs\n", time_taken);
}
