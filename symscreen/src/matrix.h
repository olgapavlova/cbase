#ifndef MATRIX_H
#define MATRIX_H

#include "headers.h"

typedef int symbol;  // перспектива — сделать отдельную сущность
#define DEFSYM 32

typedef symbol ** matrix;

/// Создать матрицу
matrix matrix_init(int, int);

/// Очистить матрицу
void matrix_clear(matrix *, int, int);

/// Очистить память под матрицу
void matrix_destroy(matrix *);

/// Заполнить матрицу символами
void matrix_fill(matrix *, symbol, int, int);

/// Вывести матрицу на экран
void matrix_show(matrix *, int, int);

void matrix_map(matrix *, matrix *, cursor *, int, int);

// WTF «Кто-то другой» знает про размерность матрицы и управляет ей

#endif
