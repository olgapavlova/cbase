#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "usual.h"
#include "menu.h"


void dbl(int * n) {
  (*n) += (*n);
}

void prn(int * n) {
  printf("%d\n", *n);
}

void stt(int * n) {
  char * int2str[10] = { "один", "два", "три",  "четыре",  "пять",  "шесть",  "семь",  "восемь",  "девять" };
  printf("%s\n", int2str[*n - 1]);
}

void sqq(int * n) {
  (*n) *= (*n);
}

static item d = { 'd', dbl };
static item p = { 'p', prn };
static item s __attribute__ ((unused))= { 's', stt };
static item q = { '^', sqq };

int main(int argc, char ** argv) {

  if(argc) {}

  // 1 аргумент — целое число от 0 до 9
  // 2 аргумент — последовательность действий с числом
  //
  // Пример: 7 ds^p^p
  //
  // d — удвоить число
  // p — напечатать текущее значение
  // s — превратить число в строку (слово) и напечатать его
  // ^ — возвести число в квадрат 

  menu * m = menu_create(3, &d, &p, &q);

  int n = (int)argv[1][0] - 48;

  menu_process(m, argv[2], &n);

  printf("\n");

  return 0;
}

