#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "menu.h"

menu * menu_create(int n, ...) {
  menu * result = malloc(sizeof(menu));
  if(result == NULL) {exit(EXIT_FAILURE);}
  result->data = malloc(n * sizeof(item));

  // 1. Массивчик из ...
  va_list args;

  // 2. Пройти по нему
  // 3. От начала
  va_start(args, n);

  // 4. И с каждым элементом
  for(int i = 0; i < n; ++i) {
    item * g = va_arg(args, item *);

    // 5. Что-то сделать
    result->data[i] = g;
    result->length++;

  }

  // 6. До конца
  va_end(args);

  return result;
}

void menu_process(menu * m, char * s, int * n) {
  char * p = s;
  while(*p != '\0') {
    item * u = menu_find(m, *p);
    if(u != NULL) {
      (u->f)(n);
    }
    p++;
  }
}

item * menu_find(menu * m, char c) {
  item * result = NULL;
  for(int i = 0; i < m->length; ++i) {
    if(m->data[i]->code == c) {
      result = m->data[i];
      break;
    }
  }
  return result;
}
