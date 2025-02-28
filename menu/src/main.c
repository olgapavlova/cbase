#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "log.h"
#include "menu.h"

int main(int argc, char ** argv) {
  
  log_init("../log/1.txt");

  menu_set * m = malloc(sizeof(menu_set));

  m->length = 1;
  m->data = malloc(sizeof(menu_item));
  m->data[0] = menu_item_create('n', next);

  if(argc == 1) { exit(EXIT_FAILURE); }

  char * command = argv[1];

  menu_process(m, command);


  free(m);
  m = NULL;

  return 0;
}

void next() {
  static char c = 32;
  if(++c == (char)128) { c = 32; }
  printf("%c", c);
}
