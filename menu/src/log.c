#include <stdio.h>
#include <stdlib.h>
#include "log.h"

void log_init(char * path) {
  freopen(path, "w", stderr);  // открыть файл для записи логов 
}


