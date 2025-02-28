#include <time.h>
#include "matrix.h"
#include "figures.h"

#ifdef MAIN_FIGURES
void _playground();

int main() {
	_playground();
}

void _playground() {

	matrix m;
	matrix_init(&m, 7, 40);
	matrix_fill(&m, ' ');
	matrix_print(&m);  // TODO How to resolve empty matrix state?
	printf("\n");

	figures_set_point_char(&m, 4, 8, '!');
	matrix_print(&m);
	printf("\n");

	figures_random_char(&m);
	matrix_print(&m);
	printf("\n");

	symbol sym = symbol_init(NULL);
	sym.character = '7';

	matrix_fill(&m, '0');
	figures_set_point(&m, 5, 12, &sym);
	matrix_print(&m);
	printf("\n");

	figures_draw_rect(&m, 1, 1, 4, 10, &sym);
	matrix_print(&m);
	printf("\n");
}
#endif

void figures_random_char(matrix * m) {  // TODO Move to matrix module?
	#ifndef RAND_MAX
	#define RAND_MAX 512
	#endif

	srand(time(NULL));

	for (int i = 0; i < m->rows; ++i) {
		for (int j = 0; j < m->cols; ++j) {
			int r = rand();
			m->data[i][j].character = (r % (126 - 32)) + 32;
		}
	}
}

void figures_set_point_char(matrix * m, int row, int col, char c) {
	m->data[row][col].character = c;
}

// TODO Add style set
void figures_set_point(matrix * m, int row, int col, symbol * sym) {
	figures_set_point_char(m, row, col, sym->character);
}

void figures_draw_rect(matrix * m, int row, int col, int h, int w, symbol * sym) {
	int rowmax = (row + h < m->rows) ? row + h : m->rows;
	int colmax = (col + w < m->cols) ? col + w : m->cols;
	for(int i = row; i < rowmax; ++i) {
		for (int j = col; j < colmax; ++j) {
			figures_set_point(m, i, j, sym);
		}
	}
}
