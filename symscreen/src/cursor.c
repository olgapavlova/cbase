#include "headers.h"

cursor * cursor_init() {
  cursor * result = malloc(sizeof(cursor));
  if(result == NULL) { exit(EXIT_FAILURE); }
  result->c = DEFCUR;
  result->prev = '\0';
  return result;
}

void cursor_set(screen * s, cursor * c, int w, int h) {
  c->w = w % s->w;
  c->h = h % s->h;
  c->prev = screen_get(s, c->w, c->h);
}

void cursor_show(screen * s, cursor * c) {
  c->hidden = 0;
  screen_show(s, c);
}

void cursor_hide(screen * s, cursor * c) {
  c->hidden = 1;
  screen_show(s, c);
}

void cursor_blink(screen * s, cursor * c) {
  cursor_hide(s, c);
  sleep(1);
  cursor_show(s, c);
}

void cursor_change(cursor * c, char ch) {
  c->c = ch;
  // WTF Вот тут бы сразу и моргнуть — но мы не знаем screen
}
