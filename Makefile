CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c99 -g
OBJECTS = huffman.o stack.o

.PHONY  :       all     clean

all     :       testing
testing :       $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o testing
encode :       $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -c encode.c -o encode
huffman.o :       huffman.c
	$(CC) $(CFLAGS) -c huffman.c
stack.o :       stack.c
	$(CC) $(CFLAGS) -c stack.c
queue.o :       queue.c
	$(CC) $(CFLAGS) -c queue.c
clean   :
	rm -f $(OBJECTS) testing encode.o 
