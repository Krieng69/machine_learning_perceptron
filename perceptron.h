#ifndef PERCEPTRON_H
#define PERCEPTRON_H

/*
 * [i][0] -- x1
 * [i][1] -- x2
 * [i][2] -- target (aka class)
 */

#define MATRIX_ROWS 4
#define MATRIX_COLS 3
#define ALPHA 1
//#define VERBOSE;

typedef int data_set_entry[MATRIX_COLS];

void parseMeta(int *rows, int *cols, char const *header, char const *path);
void parseData(data_set_entry *x_data, char const *header, char const *path);

#endif // PERCEPTRON_H
