/**
 * @file menu.c
 * @brief Реализация функций работы с меню библиотеки libmenu
 */

#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "log.h"

void menu_process(menu_set * m, char * line) {
  char * p = line;
  while(*p != '\0') {
    menu_item * current = menu_find_item(m, *p);
    if(current != NULL) { printf("+"); }
    ++p;
  }
  printf("\n");

}

menu_item * menu_item_create(char c, menu_f f) {
  menu_item * result = malloc(sizeof(menu_item));
  if(result == NULL) { Ls("Не удалось выделить память под пункт меню"); exit(EXIT_FAILURE); }
  result->code = c;
  result->f = f;
  return result;
}

menu_item * menu_find_item(menu_set * m, char c) {
  menu_item * result = NULL;
  for(int i = 0; i < m->length; ++i) {
    if(m->data[i]->code == c) { result = m->data[i]; break; }
  }
  return result;
}
