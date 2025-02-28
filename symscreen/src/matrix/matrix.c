#include "matrix.h"
#include "symbol.h"
#include <stdlib.h>

#ifdef MAIN_MATRIX
void _playground();

int main() {
	_playground();
}

void _playground() {
	matrix a;
	matrix_init(&a, 14, 72);
	matrix_fill(&a, '-');
	matrix_print(&a);
	matrix_fill(&a, 'Q');
	matrix_print(&a);
	matrix_destroy(&a);
}
#endif

void matrix_init(matrix * a, int rows, int cols) {
	symbol ** temp = malloc(sizeof(symbol *) * rows);
	temp[0] = malloc(sizeof(symbol) * rows * cols);
	for (int i = 1; i < rows; ++i) temp[i] = temp[i-1] + cols;
	a->data = temp;
	a->rows = rows;
	a->cols = cols;
	matrix_init_data(a);
}

void matrix_destroy(matrix * a) {
	free(a->data[0]);
	free(a->data);
}

void matrix_init_data(matrix * a) {
	for (int i = 0; i < a->rows; i++) {
		for (int j = 0; j < a->cols; j++) {
			a->data[i][j] = symbol_init(NULL);
		}
	}
}

void matrix_fill(matrix * a, char c) {
	for (int i = 0; i < a->rows; i++) {
		for (int j = 0; j < a->cols; j++) {
			(*a).data[i][j].character = c;
		}
	}
}

void matrix_print(matrix * a) {
	for (int i = 0; i < a->rows; i++) {
		for (int j = 0; j < a->cols; j++) {
			a->data[i][j].print(a->data[i][j]);
		}
		printf("\n");
	}
}
