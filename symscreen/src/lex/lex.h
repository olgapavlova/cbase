#pragma once

/*
 * Work with dynamic string -- lexems
 */

typedef char *lex;

lex lex_init();             // Init lexem
lex lex_init_from_stdin();  // Read lexem from stdin
void lex_destroy(lex *);    // Destroy lexem

void lex_add_char(lex *, char);    // Add symbol to the end of lexem
void lex_add_word(lex *, char *);  // Add string to the end of lexem

int lex_len(lex *);  // Lexem lenght; -1 -- error
