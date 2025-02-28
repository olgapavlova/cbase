#pragma once
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "style.h"

struct symbol {
    char character;
    int ignore_stl;
    style *stl;
    void (*print)(struct symbol);
};
typedef struct symbol symbol;

symbol symbol_init(style *);
int symbol_read_from_stdin(symbol *);
void symbol_form_style_string(symbol, char (*)[100]);
void symbol_print(symbol);
