CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c99 -g
OBJECTS = stack.o

.PHONY	:	all	clean

all	:	stack
huffman.o :	huffman.c
	$(CC) $(CFLAGS) -c huffman.c
stack.o	:	stack.c
	$(CC) $(CFLAGS) -c stack.c
clean	:
	rm -f $(OBJECTS) stack
