.PHONY: all clean

CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
ALL_O = main.o cursor.o menu.o matrix.o screen.o

PLAY_FLAG = -DMAIN_PLAY
all: main.play

%.o: %.c
	$(CC) $(CFLAGS) $(PLAY_FLAG) -c $< -o $@

%.play: $(ALL_O)
	$(CC) $(CFLAGS) $^ -o $*.play

clean:
	rm -f *.o
	rm -f *.play
