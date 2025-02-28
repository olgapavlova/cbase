/**
 * @file menu.h
 * @brief Публичный интерфейс библиотеки libmenu
 */

#ifndef MENU_H_LOADED
#define MENU_H_LOADED

typedef void (*menu_f)(void);

/// Элемент пункта меню
typedef struct menu_item {
  char code;  /**< Буква, по которой вызываем функцию */
  menu_f f;   /**< Функция пункта меню */
} menu_item;

/// Набор пунктов меню
typedef struct menu_set {
  int length;        /**< Длина меню */
  menu_item ** data;  /**< Первый элемент массива из пунктов меню */
} menu_set;

menu_item * menu_item_create(char, menu_f);

/// Обработать строку как последовательность команд
void menu_process(menu_set *, char *);

/// Найти пункт меню
menu_item * menu_find_item(menu_set *, char);

#endif
