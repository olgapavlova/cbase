#ifndef SCREEN_H
#define SCREEN_H

#include "headers.h"

struct screen {
	int w;
	int h;
	matrix bg;  //! двумерный массив чисел; не ссылка!
	matrix out;  //! результат сборки всех слоёв (пока два)
};

/// Создать экран
screen * screen_init(int, int);

/// Залить экран символом
void screen_fill(screen *, char);

/// Показать экран
void screen_show(screen *, cursor *);

/// Удалить экран (и из памяти тоже)
void screen_destroy(screen **);

/// Установить точку экрана в значение
void screen_set(screen *, char, int, int); 

/// Получить значение из точки экрана
char screen_get(screen *, int, int);

/// Сохранить экран в файл
void screen_save(screen *);

/// Загрузить экран из файла
void screen_load(screen *);

#endif
