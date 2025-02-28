#pragma once
/*
 * Internal decode rules declaration
 */

int _decode_normalize(limit *, int);  // check value and set to default
int _decode(limit *, int);
int _decode_weight(limit *, int);
int _decode_shift(limit *, int);      // is + (0|1) * shift
int _decode_asis(limit *, int);       // 1 -- .is, 0 -- .is + 20

static style_limits _style_limits = {  // ANSI codes limitations
	.weight = {.by_default = 0, .shift = 22, .min = -1, .max = 1, .decode = _decode_weight },
	.underline = {.by_default = 0, .shift = 20, .is = 4, .min = 0, .max = 1, .decode = _decode_asis },
	.hide = {.by_default = 0, .shift = 20, .is = 8, .min = 0, .max = 1, .decode = _decode_asis },
	.crossed = {.by_default = 0, .shift = 20, .is = 9, .min = 0, .max = 1, .decode = _decode_asis },
	.text = {.by_default = 7, .shift = 30, .min = 0, .max = 7, .decode = _decode_shift },
	.bg = {.by_default = 0, .shift = 40, .min = 0, .max = 7, .decode = _decode_shift },
	.inverse = {.by_default = 0, .shift = 20, .is = 7, .min = 0, .max = 1, .decode = _decode_asis }
};

void _add_ansi_param(lex *, limit *, int);
void _add_semicolumn_and_ansi_param(lex *, limit *, int);

