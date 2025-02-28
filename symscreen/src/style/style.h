#pragma once
#include <assert.h>
#include <lex.h>
#include <stdio.h>
#include <stdlib.h>

struct style_decor {
    int weight;  // undef or 22 -- normal, 1 -- bold, 2 -- light
    int underline;
    int hide;
    int crossed;
};
typedef struct style_decor style_decor;

struct style_color {
    int text;
    int bg;
    int inverse;
};
typedef struct style_color style_color;

struct style {
    style_decor decor;
    style_color color;
};
typedef struct style style;

struct limit {
	int by_default;
	int is;
	int shift;
	int min;
	int max;
	int (*decode)(struct limit *, int);
};
typedef struct limit limit;

struct style_limits {
	limit weight;
	limit underline;
	limit hide;
	limit crossed;
	limit text;
	limit bg;
	limit inverse;
};
typedef struct style_limits style_limits;

style style_init();
int style_read_from_stdin(style *);
void style_generate_esc_string(style *, lex *);
void style_print_char(style *, char);
void style_print_word(style *, lex);
void style_print_default();
void style_normalize(style *, style_limits *);
