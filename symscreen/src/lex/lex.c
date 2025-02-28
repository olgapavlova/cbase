#include "lex.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef MAIN_LEX
void _playground();  // for all lex functions

int main() { _playground(); }

// Playground shows all necessary behaviour; not testing yet, though
void _playground() {
    printf("NULL length:\t%d\n", lex_len(NULL));  // == -1

    char* r = lex_init();                        // empty lex
    printf("Empty length:\t%d\n", lex_len(&r));  // == 0

    lex_destroy(&r);  // free memory to init again
    printf("Input lex:\t");

    r = lex_init_from_stdin();  // init and input until Enter, char by char
    printf("Lex:\t\t%s\n", r);
    printf("Lex length:\t%d\n", lex_len(&r));  // char counter

    lex_add_char(&r, '+');  // add character to the end of lex
    printf("Lex+:\t\t%s\n", r);
    printf("Lex+ length:\t%d\n", lex_len(&r));  // previous counter + 1

    lex_add_word(&r, "e[123;");  // add word to the end of lex
    printf("Lex+w:\t\t%s\n", r);
    printf("Lex+w length:\t%d\n", lex_len(&r));  // previous counter + 1

    lex_destroy(&r);  // to free memory
    printf("Lex+ destroyed.\n");
}
#endif

/*
 * Public functions implementation
 */

lex lex_init() {
    lex result = malloc(sizeof(char));
    if (result != NULL) result[0] = '\0';
    return result;
}

lex lex_init_from_stdin() {
    lex result = lex_init();
    char c = '\0';
    while (scanf("%c", &c) == 1 && c != '\n') lex_add_char(&result, c);
    return result;
}

void lex_destroy(lex* lx) { free(*lx); }

int lex_len(lex* lx) {
    int result = 0;
    char c = '\0';
    if (lx != NULL)
        while ((c = (*lx)[result]) != '\0') ++result;
    else
        result = -1;
    return result;
}

void lex_add_char(lex* lx, char c) {
    int lx_len = lex_len(lx);
    *lx = realloc(*lx, (lx_len + 2) * sizeof(char));
    if (*lx != NULL) {
        (*lx)[lx_len] = c;
        (*lx)[lx_len + 1] = '\0';
    }
}

void lex_add_word(lex* lx, char* w) {  // TODO Replace char to lex?
    int w_len = 0;
    for (int i = 0; w[i] != '\0'; ++i) ++w_len;
    int lx_len = lex_len(lx);
    *lx = realloc(*lx, lx_len + w_len + 1);  // similar to lex_add_char
    if (*lx != NULL) {
        for (int i = 0; i < w_len; ++i) (*lx)[lx_len + i] = w[i];
        (*lx)[lx_len + w_len] = '\0';
    }
}
