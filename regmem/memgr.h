#ifndef MEMGR_H
#define MEMGR_H

#include <stddef.h>

/// Выделить динамическую память
void * memgr_calloc(int, size_t);

/// Очистить всю динамическую память
void memgr_destroy_all_memory(void);

#endif
