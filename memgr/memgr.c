#include "memgr.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// Тип «Реестр выделенной динамической памяти»
typedef struct memreg_t {
  int length;
  void ** data; // [ * * * ... * {тут length} ] 
} memreg_t;

// Создать новый реестр динамической памяти или отдать тот, что уже есть
static memreg_t * _memreg(void) {
  static memreg_t * result = NULL;
  if (result == NULL) {
      result = calloc(1, sizeof(memreg_t));
      result->length = 0;
      result->data = NULL;
      atexit(memgr_destroy_all_memory);
  }
  if (result == NULL) { exit(EXIT_FAILURE); }
  return result;
}

// Зарегистрировать память в реестре
static void _add_to_memreg(void * v) {
  memreg_t * _mr = _memreg();
  // выделить память под ещё один элемент в _mr->data
    void ** tmp = malloc(sizeof(void *) * (_mr->length + 1));
    if(tmp == NULL) { exit(EXIT_FAILURE); }
    memcpy(tmp, _mr->data, sizeof(void*) * (_mr->length));
    free(_mr->data);
    _mr->data = tmp;
    tmp = NULL;

  // записать элемент последним в _mr->data
  _mr->data[_mr->length++] = v;
}

/// Выделить динамическую память
void * memgr_calloc(int n, size_t size) {
  void * result;
  result = calloc(n, size);
  if(result == NULL) { exit(EXIT_FAILURE); }
  _add_to_memreg(result);
  return result;
}

/// Очистить всю динамическую память
void memgr_destroy_all_memory(void) {
  memreg_t * _mr = _memreg();
  int l = _mr->length;
  for(int i = l - 1; i >=0; i--) {
    free(_mr->data[i]);
    _mr->data[i] = NULL;
    _mr->length--;
  }
  free(_mr->data);
  free(_mr);
}

#ifdef TEST
int main(void) {
  int * a = memgr_calloc(1, sizeof(int));
  int * b = memgr_calloc(1, sizeof(int));
  if(a || b) {}

  return EXIT_SUCCESS;
}
#endif
