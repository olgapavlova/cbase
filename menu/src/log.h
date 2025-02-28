/**
 * @file log.h
 * @brief Логирование поведения системы при установленном LOG_ON
 */
#ifndef LOG_H_LOADED
#define LOG_H_LOADED

#include <stdio.h>

#define LOG_INT_MAX_LENGTH 50

#ifdef LOG_ON
    #define LOG_C_VERSION (__STDC_VERSION__ == 201112L) ? "C11" : "C??"

    #define Li(x) do { \
          char message[LOG_INT_MAX_LENGTH] = {}; \
          sprintf(message, "%d", (x)); \
          Ls(message) \
      } while (0);  // целое

    #define Ls(x) fprintf(stderr, "%s [%s] %s:%d %s() %s\n", LOG_C_VERSION, __TIME__, \
          __FILE__, __LINE__, __FUNCTION__, (x));  // строка

    #define LN Ls("")  // пусто (ничего дополнительного)

#else
    #define Li(x)
    #define Ls(x)
    #define LN 
#endif

void log_init(char *);

#endif
