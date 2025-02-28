/**
 * @file regmem.h
 * @brief Работа с динамической памятью. Объявления
 */
#ifndef REGMEM_H
#define REGMEM_H

/// Выделить и зарегистрировать в реестре запрошенный объём памяти
void *regmem_calloc(size_t, size_t);

/// Изменить размер памяти по указателю
void regmem_realloc(void **, size_t, size_t);

/// Освободить всю память
void regmem_destroy();

#endif
