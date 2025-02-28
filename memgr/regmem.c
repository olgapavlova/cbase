/**
 * @file regmem.h
 * @brief Работа с динамической памятью. Реализация
 */
#include "cbase.h"

// Тип данных для реестра динамической памяти
// Снаружи не нужен и даже вреден, поэтому живёт в файле реализации
typedef struct regmem {
  int length;   // длина реестра
  void **data;  // данные — массив void*-указателей
} regmem;

// Получить ссылку на реестр динамической памяти
static regmem *_get() {
  static regmem *result = NULL;
  if (result == NULL) {
    result = calloc(1, sizeof(regmem));
  }
  if (result == NULL) {
    STOP(Не удалось создать реестр динамической памяти, EXIT_FAILURE);
  }
  return result;
}

// Очистить память под указателем и сам указатель
static void _destroy_item(void **pp) {
  free(*pp);
  *pp = NULL;  // ради этого двойной указатель
}

// Добавить указатель в реестр
static void _add(void *p) {
  regmem *_r = _get();
  _r->length++;
  _r->data = realloc(
      _r->data,
      (_r->length) * sizeof(void *));  // внутри модуля — низкоуровневые функции
  if (_r->data == NULL) {
    STOP(Не удалось изменить длину реестра динамической памяти, EXIT_FAILURE);
  }
  _r->data[_r->length - 1] = p;
}

// Заменить один указатель на другой (нужно при realloc)
static void _replace(void *to, void *from) {
  regmem *_r = _get();
  void **p = _r->data;
  int counter = 0;

  while ((*p != from) && (counter < _r->length)) {  // ищем старый указатель
    p++;
    counter++;
  }

  if (counter == _r->length) {
    STOP(Указатель не найден в реестре, EXIT_FAILURE);
  } else {
    _r->data[counter] = to;
  }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/// Выделить и зарегистрировать в реестре запрошенный объём памяти
void *regmem_calloc(size_t quantity, size_t one_size) {
  if ((one_size == 0) || (quantity == 0)) {
    STOP(Запрос на выделение памяти нулевого размера, EXIT_FAILURE);
  }
  void *result = calloc(quantity, one_size);
  if (result == NULL) {
    STOP(Не удалось выделить память, EXIT_FAILURE);
  }
  _add(result);
  return result;
}

/// Изменить размер памяти по указателю
void regmem_realloc(void **v, size_t size_new, size_t size_old) {
  void *tmp = malloc(size_new);
  if (tmp == NULL) {
    STOP(Не удалось изменить размер памяти, EXIT_FAILURE);
  } else {
    int cpy_size = (size_old > size_new) ? size_new : size_old;
    memcpy(tmp, *v, cpy_size);
    _replace(tmp, *v);
    free(*v);
    *v = tmp;
  }
}

/// Освободить всю динамическую память
void regmem_destroy() {
  regmem *_r = _get();
  while (_r->length > 0) {
    _destroy_item(&(_r->data[_r->length-- - 1]));
  }
  free(_r->data);
  _r->data = NULL;
  free(_r);  // очищаем память из-под самого реестра
}
