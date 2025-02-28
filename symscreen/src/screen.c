#include "headers.h"

#ifdef SCREEN_PLAY
void _playground();

int main() { _playground(); }

void _playground() {
  screen * s = screen_init(72, 14);
  screen_fill(s, '0');
  screen_show(s);
  screen_fill(s, '@');
  screen_show(s);
  screen_set(s, '!', 7, 12);
  screen_show(s);
}
#endif

static void _clear() {
  printf("\033[2J");
  printf("\033[H");
}

static void _hide_system_cursor() {
  printf("\033[?25l");
  fflush(stdout);
}

screen * screen_init(int w, int h) {
  screen * result = malloc(sizeof(screen));
  if(result == NULL) { exit(EXIT_FAILURE); }
  result->w = w;
  result->h = h;
  result->bg = matrix_init(w, h);
  result->out = matrix_init(w, h);
  if(result->bg == NULL) { exit(EXIT_FAILURE); }
  if(result->out == NULL) { exit(EXIT_FAILURE); }
  return result;
}

void screen_fill(screen * s, char c) {
  matrix_fill(&(s->bg), (int)c, s->w, s->h);
}

void screen_show(screen * s, cursor * c) {
  _clear();
  if(!c->hidden) {
    matrix_map(&(s->out), &(s->bg), c, s->w, s->h);
    matrix_show(&(s->out), s->w, s->h); }
  else {
    matrix_show(&(s->bg), s->w, s->h);
  }
  _hide_system_cursor();
}

void screen_destroy(screen ** s) {
  matrix_destroy(&((*s)->bg));
  free(*s);
  *s = NULL;
}

void screen_set(screen * s, char c, int cw, int ch) {
  cw = cw % s->w;
  ch = ch % s->h;

  s->bg[ch][cw] = (symbol)c;
}

char screen_get(screen * s, int w, int h) {
  w = w % s->w;
  h = h % s->h;

  return (char)s->bg[h][w];
}
