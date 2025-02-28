#include "headers.h"

menu * menu_get() {
  static menu * m = NULL;

  if(m == NULL) {
    m = malloc(sizeof(menu));  // WTF динамическая память, неприятно
    if(m == NULL) { exit(EXIT_FAILURE); }
    atexit(menu_destroy);

    (*m)[(int)'c'] = menu_command_clear;
    (*m)[(int)'@'] = menu_command_at;
    (*m)[(int)' '] = menu_command_cursor_blink;
    (*m)[(int)'h'] = menu_command_cursor_hide;
    (*m)[(int)'s'] = menu_command_cursor_show;
    
    for(int i = 0; i < 128; i++) {
      if((*m)[i] == NULL) {(*m)[i] = menu_command_cursor_change; }
    }
  }

  return m;
}

void menu_run(screen * s, cursor * c, char ch) {
  menu * m = menu_get();
  void* val[3] = {s, c, &ch};
  if ((*m)[(int)ch] != NULL) {
    (*m)[(int)ch](val);
  }
}


char menu_key() {
  struct termios oldt, newt;
  char result;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  read(STDIN_FILENO, &result, 1);
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  return result;
}


void menu_command_clear(void ** p_s_c_ch) {
  screen * s = p_s_c_ch[0];
  cursor * c = p_s_c_ch[1];
  screen_fill(s, DEFSYM);
  screen_show(s, c);
}

void menu_command_at(void ** p_s_c_ch) {
  screen * s = p_s_c_ch[0];
  cursor * c = p_s_c_ch[1];
  screen_fill(s, '@');
  screen_show(s, c);
}

void menu_command_cursor_blink(void ** p_s_c) {
  screen *s = p_s_c[0];
  cursor *c = p_s_c[1];
  cursor_blink(s, c);
}

void menu_command_cursor_change(void ** p_s_c_ch) {
  screen *s = p_s_c_ch[0];
  cursor *c = p_s_c_ch[1];
  char *ch = p_s_c_ch[2];

  cursor_change(c, *ch);
  screen_show(s, c);
}

void menu_command_cursor_hide(void ** p_s_c ) {
  screen * s = p_s_c[0];
  cursor * c = p_s_c[1];
  cursor_hide(s, c);
}

void menu_command_cursor_show(void ** p_s_c ) {
  screen * s = p_s_c[0];
  cursor * c = p_s_c[1];
  cursor_show(s, c);
}

void menu_destroy() {
  menu * q = menu_get();
  free(q);
  q = menu_get();
  printf("\nА вот тут меню ещё есть, но указывает в никуда.\nВот его адрес: %p\n", q);
}
