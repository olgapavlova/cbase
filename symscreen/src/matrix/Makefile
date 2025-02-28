.PHONY: all clean test

CC = gcc
CFLAGS = -Wall -Werror -Wextra
MAKE = make
DFLAGS = 

HEADERS_DIR = ../include
HFLAGS = -isystem $(HEADERS_DIR)


matrix.a: matrix.o ../symbol/symbol.o
	ar rc $@ $<
	$(MAKE) clean
	ls -la

test: DFLAGS = -DMAIN_MATRIX
test: ALL_FLAGS = $(CFLAGS) $(DFLAGS) $(HFLAGS)
test: matrix.o ../symbol/symbol.o
	$(CC) $(ALL_FLAGS) $^ -o $@
	$(MAKE) clean
	ls -la

matrix.o: matrix.c matrix.h
	$(CC) -c $(ALL_FLAGS) $< -o $@

clean:
	rm -f *.o
	rm -f *.out
