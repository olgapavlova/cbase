#include "headers.h"

int main(int argc, char ** argv) {

  int w = (argc <= 1) ? 72 : atoi(argv[1]);
  int h = (argc <= 2) ? 14 : atoi(argv[2]);

  screen * s = screen_init(w, h);
  cursor * c = cursor_init();

  screen_fill(s, ':');
  cursor_set(s, c, s->w / 2, s->h / 2);
  screen_show(s, c);

  char ch = '\0';
  while((ch = menu_key()) != '\n') {
    menu_run(s, c, ch);
  }

  menu_run(s, c, 'c');

}
