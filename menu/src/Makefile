.PHONY: now all clean doc

CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
LOG_FLAG = -DLOG_ON
DEBUG_FLAG = -g -O0
TEST_FLAG = -DCHECK_LEVEL=CK_VERBOSE -lcheck -lpthread -lm

TEST_DIR = ../test/
BUILD_DIR = ../build/

USUAL_O = menu.o usual.o

all: usual.run clean

usual.run: $(USUAL_O)
	@$(CC) $(CFLAGS) $(LOG_FLAG) $(DEBUG_FLAG) $^ -o $(BUILD_DIR)$@

%.test: $(ALL_O) $(TEST_DIR)test_%.c
	@$(CC) $(CFLAGS) $(LOG_FLAG) $(DEBUG_FLAG) $^ -o $(BUILD_DIR)$@ $(TEST_FLAG)

%.o: %.c
	@$(CC) $(CFLAGS) $(LOG_FLAG) $(DEBUG_FLAG) -c $^ -o $@

clean:
	@rm *.o

doc:
	@doxygen Doxyfile
