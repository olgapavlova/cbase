.PHONY: all clean test

CC = gcc
CFLAGS = -Wall -Werror -Wextra
MAKE = make
DFLAGS = 
IFLAGS = -I../include/

symbol.a: symbol.o
	ar rc $@ $<
	$(MAKE) clean
	ls -la

test: DFLAGS = -DMAIN_SYMBOL
test: symbol.o ../style/style.o
	$(CC) $(CFLAGS) $(DFLAGS) $(IFLAGS) $^ -o $@
	$(MAKE) clean
	ls -la

symbol.o: symbol.c symbol.h
	$(CC) -c $(CFLAGS) $(DFLAGS) $(IFLAGS) $< -o $@

clean:
	rm -f *.o
	rm -f *.out
