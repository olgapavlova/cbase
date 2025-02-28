#include <symbol.h>

#include <stdio.h>
#include <stdlib.h>
#include <lex.h>

#include <style.h>
#include <lex.h>

#ifdef MAIN_SYMBOL
void _playground();
int main() {
	_playground();
}

void _playground() {
    style stl = style_init();
    printf("w u h c t b i:\t");
    style_read_from_stdin(&stl);  // read style from stdin (preparation)

    printf("c i:\t\t");
    symbol c = symbol_init(&stl);  // create symbol based on style

		// symbol d = symbol_init(NULL);  TODO Add null initiation

    symbol_read_from_stdin(&c);  // get symbol and ignore_stl from stdin

    printf("Symbol:\t\t");
    c.print(c);		// print symbol in style
    printf("\n");

		stl.color.inverse = 1 - stl.color.inverse;  // change style, not symbol
    printf("Change style:\t");
    c.print(c);  // print the same symbol but in changed style
    printf("\n");

		style stl2 = stl;  // create another style TODO Check if style can use =
		stl2.decor.underline = 1 - stl2.decor.underline;
		stl2.color.inverse = 1 - stl2.color.inverse;
		c.stl = &stl2;  // change style object for symbol
    printf("Switch style:\t");
    c.print(c);  // print the same symbol with new style object  
    printf("\n");
}
#endif

symbol symbol_init(style* stl) {
    symbol result = {0};
    result.stl = stl;
    result.print = symbol_print;
    return result;
}

void symbol_print(symbol sym) {
    lex stl = lex_init();
    style_generate_esc_string(sym.stl, &stl);
    printf("%s%c", stl, sym.character);
    style_print_default();
		lex_destroy(&stl);
}

int symbol_read_from_stdin(symbol* sym) {
    int read_ok = 1;
    char c;
    symbol s = *sym;
    if ((scanf("%c %d%c", &s.character, &s.ignore_stl, &c) == 3) && (c == '\n'))
        *sym = s;

    else
        read_ok = 0;

    return read_ok;
}
