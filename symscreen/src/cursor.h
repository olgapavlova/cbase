#ifndef CURSOR_H
#define CURSOR_H

#include "headers.h"

#define DEFCUR '_'

/// Тип данных «Курсор» — структура
typedef struct cursor {
	int w;
	int h;
	char c;
	char prev;  //! что тут было до курсора
	bool hidden;
} cursor;

/// Создать курсор
cursor * cursor_init();

/// Установить курсор в точку
void cursor_set(screen *, cursor *, int, int);

/// Моргнуть курсором
void cursor_blink(screen *, cursor *);

void cursor_show(screen *, cursor *);
void cursor_hide(screen *, cursor *);

/// Сдвинуть курсор вверх
void cursor_up(cursor *);

/// Сдвинуть курсор вниз
void cursor_down(cursor *);

/// Сдвинуть курсор вправо
void cursor_right(cursor *);

/// Сдвинуть курсор влево
void cursor_left(cursor *);

/// Поменять курсорный символ
void cursor_change(cursor *, char);


#endif
