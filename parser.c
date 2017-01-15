#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "perceptron.h"

char const validChars[] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-'
};

/* currently unused!
char const ignorePattern[] = {'-', ' ', '\t', '\n'};
const int ignorePatternSize = sizeof(ignorePattern) / sizeof(ignorePattern[0]);
*/

void parseMeta(int *rows, int *cols, const char *header, const char *path) {
	FILE *fptr = fopen(path, "r");
	printf("%s: enter, header: %s\n", __func__, header);

	if (!fptr) {
		printf("%s: error reading from file: %s\n", __func__, path);
		return;
	}

	char *buffer = NULL;
	size_t len = 0;
	while (!feof(fptr)) {
		getline(&buffer, &len, fptr);

		if (strncmp(buffer, header, strlen(header)) == 0) {
			printf("%s: found header, header: %s\n", __func__, header);
			// we found the header, now get the next line
			getline(&buffer, &len, fptr);

			int mat_cols = 0;
			// look for valid chars
			for (int i = 0; i < strlen(buffer); i++) {
				for (int j = 0; j < (sizeof(validChars) / sizeof(validChars[0])); j++) {
					if (buffer[i] == validChars[j]) {
						printf("%s: found valid char, header: %s\n", __func__, header);
						// do not count signs
						if (buffer[i] != '-')
							mat_cols++;
						break;
					}
				}
			}
			printf("%s: set cols, header: %s\n", __func__, header);
			*cols = mat_cols;

			// matrix rows
			int mat_rows = 0;
			while (buffer[0] != '\n' && buffer[0] != EOF) {
				printf("%s: read buffer: %s for rows, header: %s\n", __func__, buffer, header);
				mat_rows++;
				getline(&buffer, &len, fptr);
			}
			*rows = mat_rows;

			break;
		}
	}

	free(buffer);
	fclose(fptr);
	printf("%s: exit, header: %s\n", __func__, header);
}

void parseData(data_set_entry *x_data, char const *header, char const *path) {
	FILE *fptr = fopen(path, "r");
	data_set_entry *data_ptr;
	printf("%s: enter, header: %s\n", __func__, header);

	if (!fptr) {
		printf("%s: error reading from file: %s\n", __func__, path);
		return;
	}

	int data_rows = 0;
	int data_cols = 0;
	parseMeta(&data_rows, &data_cols, header, "data.txt");

	char *buffer = NULL;
	size_t len = 0;
	while (!feof(fptr)) {
		getline(&buffer, &len, fptr);

		if (strncmp(buffer, header, strlen(header)) == 0) {
			data_ptr = x_data;

			int found = 0;
			int col_offset = 0;
			for (int i = 0; i < data_rows; i++) {
				// we found the header, now get the next line
				getline(&buffer, &len, fptr);

				// look for valid chars
				for (int j = 0; j < strlen(buffer); j++) {
					for (int k = 0; k < (sizeof(validChars) / sizeof(validChars[0])); k++) {
						if (buffer[j] == validChars[k]) {
							// do not count signs
							char *entry_str = NULL;
							if (buffer[j] != '-') {
								entry_str = malloc(sizeof(char)+2);
								entry_str[0] = buffer[j];
								entry_str[1] = '\0';
							} else {
								entry_str = malloc(sizeof(char)+3);
								entry_str[0] = buffer[j];
								entry_str[1] = buffer[j+1];
								entry_str[2] = '\0';
								j++;
							}
							printf("%s: found valid string: %s\n", __func__, entry_str);
							// NULL endptr, decimal(10) base
							*(col_offset+data_ptr[i]) = strtol(entry_str, NULL, 10);
							col_offset++;
							// reset offset if necessary
							if (col_offset == data_cols)
								col_offset = 0;

							free(entry_str);
							found++;
							break;
						}
					}
				}
			}
		}
	}

	free(buffer);
	fclose(fptr);
}
