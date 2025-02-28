.PHONY: all val clean
.SILENT: all val clean

CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
TEST_FLAGS = -DTEST

all: clean memgr val

memgr: memgr.c
	$(CC) $(CFLAGS) $(TEST_FLAGS) $^ -o $@

val: memgr
	valgrind --leak-check=full --show-leak-kinds=all --tool=memcheck -s ./$^

clean: 
	rm -f *.o
	rm -f *.test
