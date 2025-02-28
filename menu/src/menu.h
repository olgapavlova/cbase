#ifndef MENU_H_LOADED
#define MENU_H_LOADED

// Функция из пункта меню
typedef void (*fm)(int *);

// Пункт меню
typedef struct item {
  char code;
  fm f;
} item;

// Меню
typedef struct menu {
  int length;
  item ** data;
} menu;

menu * menu_create(int, ...);

void menu_process(menu *, char *, int *);

item * menu_find(menu *, char);

#endif
