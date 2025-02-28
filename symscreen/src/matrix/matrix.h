#pragma once
#include "symbol.h"
#include <stdlib.h>

struct matrix {
	symbol ** data;
	int rows;
	int cols;
};
typedef struct matrix matrix; 

void matrix_init(matrix *, int, int);
void matrix_init_data(matrix *);
void matrix_destroy(matrix *);
void matrix_fill(matrix *, char);
void matrix_print(matrix *);
