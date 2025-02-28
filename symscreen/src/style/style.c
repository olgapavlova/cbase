#include <lex.h>
#include <stdio.h>
#include <stdlib.h>
#include <style.h>
#include "decode.h"

#ifdef MAIN_STYLE
/*
 * Main part; for test purposes only
 */

void _playground();

int main() { _playground(); }

void _playground() {
    style s = style_init();  // init pseudo object

    printf("w u h c t b i:\t");
    style_read_from_stdin(&s);  // hint explains order

		style_normalize(&s, &_style_limits);  // normalize accordingly to preset

    printf("char:\t\tN");
    style_print_char(&s, 'W');  // print character in style
    printf("N\n");

    printf("word:\t\t");
    style_print_word(&s, "1 2=3-4+5/6#7@8!9.0,");  // print word in style
    printf("\n");
}
#endif


/*
 * Public API functions implementations (see style.h for declarations)
 */

style style_init() {  // in case we need more logic
    style result = {0};
    return result;
}

void style_generate_esc_string(style* s, lex* esc) {
		if (s != NULL) {
    lex_add_word(esc, "\e[");

		_add_ansi_param(esc, &_style_limits.weight, s->decor.weight);
		_add_semicolumn_and_ansi_param(esc, &_style_limits.underline, s->decor.underline);
		_add_semicolumn_and_ansi_param(esc, &_style_limits.crossed, s->decor.crossed);
		_add_semicolumn_and_ansi_param(esc, &_style_limits.hide, s->decor.hide);
		_add_semicolumn_and_ansi_param(esc, &_style_limits.text, s->color.text);
		_add_semicolumn_and_ansi_param(esc, &_style_limits.bg, s->color.bg);
		_add_semicolumn_and_ansi_param(esc, &_style_limits.inverse, s->color.inverse);

    lex_add_char(esc, 'm');
		}
}

void style_print_word(style* stl, lex w) {  // TODO Check if lex is OK here
    lex esc = lex_init();
    style_generate_esc_string(stl, &esc);
    printf("%s%s", esc, w);
    style_print_default();
    lex_destroy(&esc);
}

void style_print_char(style* stl, char c) {
    lex esc = lex_init();
    style_generate_esc_string(stl, &esc);
    printf("%s%c", esc, c);
    style_print_default();
    lex_destroy(&esc);
}

int style_read_from_stdin(style* stl) {
    int read_ok = 1;
    char c;
    style s = style_init();
    if (scanf("%d %d %d %d %d %d %d%c", &s.decor.weight, &s.decor.underline, &s.decor.hide,
              &s.decor.crossed, &s.color.text, &s.color.bg, &s.color.inverse, &c) == 8 &&
        c == '\n')
        *stl = s;

    else
        read_ok = 0;

    return read_ok;
}

void style_print_default() { printf("\e[0m"); }

void style_normalize(style * stl, style_limits * stlm) {
	stl->decor.weight = _decode_normalize(&(stlm->weight), stl->decor.weight);
	stl->decor.underline = _decode_normalize(&(stlm->underline), stl->decor.underline);
	stl->decor.hide = _decode_normalize(&(stlm->hide), stl->decor.hide);
	stl->decor.crossed = _decode_normalize(&(stlm->crossed), stl->decor.crossed);
	stl->color.text = _decode_normalize(&(stlm->text), stl->color.text);
	stl->color.bg = _decode_normalize(&(stlm->bg), stl->color.bg);
	stl->color.inverse = _decode_normalize(&(stlm->inverse), stl->color.inverse);
}

int _decode_normalize(limit * lm, int value) {
	int result = lm->by_default;
	if (value >= lm->min && value <= lm->max) result = value;
	return result;
}

int _decode_weight(limit * lm, int weight) {
	int result = weight;
	if(weight == -1) result = 2;
	if(weight == 0) result = lm->shift;  // to avoid compilation error (lm usage)
	return result;
}

int _decode_shift(limit * lm, int value) {
	return value + lm->shift;
}

int _decode_asis(limit * lm, int value) {
	int result = lm->is + (1 - value) * lm->shift;
	return result;
}

int _decode(limit * lm, int value) {
		int result = lm->decode(lm, value);
		return result;
}

void _add_ansi_param(lex * esc, limit * lm, int value) {
		int dec = lm->decode(lm, value);
		char buffer[10] = {0};
		sprintf(buffer, "%d", dec);
		lex_add_word(esc, buffer);
}

void _add_semicolumn_and_ansi_param(lex * esc, limit * lm, int value) {
		lex_add_char(esc, ';');
		_add_ansi_param(esc, lm, value);
}
