#include "headers.h"

#ifdef MATRIX_PLAY
void _playground();

int main() {
	_playground();
}

void _playground() {
	matrix a = matrix_init(72, 14);
	matrix_fill(&a, 60, 72, 14);
	matrix_show(&a, 72, 14);
	matrix_clear(&a, 72, 14);
	matrix_show(&a, 72, 14);
	matrix_destroy(&a);
}
#endif

matrix matrix_init(int w, int h) {
	symbol ** result = malloc(sizeof(symbol *) * h);
  if(result == NULL) { exit(EXIT_FAILURE); }
	result[0] = malloc(sizeof(symbol) * w * h);
  if(result[0] == NULL) { exit(EXIT_FAILURE); }
	for (int i = 1; i < h; ++i) { result[i] = result[i-1] + w; }
  return result;
}

void matrix_destroy(matrix * a) {
	free((*a)[0]);
	free(*a);
  *a = NULL;
}

void matrix_clear(matrix * a, int w, int h) {
  matrix_fill(a, DEFSYM, w, h);
}

void matrix_fill(matrix * a, symbol c, int w, int h) {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			(*a)[i][j] = c;
		}
	}
}

void matrix_show(matrix * a, int w, int h) {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			printf("%c", (char)(*a)[i][j]);  // WTF Зависим от того, что символ — это int
		}
		printf("\n");
	}
}

void matrix_map(matrix *to, matrix *bg, cursor * c, int w, int h) {
  if(bg) {};
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			(*to)[i][j] = ((i == c->h) && (j == c->w)) ? c->c : (*bg)[i][j];
		}
	}
}
