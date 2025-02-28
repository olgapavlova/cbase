#ifndef MENU_H
#define MENU_H

#include "headers.h"

typedef void (*command)(void **);

typedef command menu[128];

menu * menu_get();
void menu_run(screen *, cursor *, char);

char menu_key();

void menu_command_clear(void **);  // очистить экран
void menu_command_at(void **);
void menu_command_cursor_blink(void **);
void menu_command_cursor_change(void **);
void menu_command_cursor_hide(void **);
void menu_command_cursor_show(void **);

void menu_destroy();

#endif
