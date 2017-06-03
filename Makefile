CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99 -g
OBJECTS = huffman.o stack.o queue.o decode.o

.PHONY  :       all     clean

all     :       decode
decode :       $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o decode
decode.o	:	decode.c
	$(CC) $(CFLAGS) -c decode.c
huffman.o :       huffman.c
	$(CC) $(CFLAGS) -c huffman.c
stack.o :       stack.c
	$(CC) $(CFLAGS) -c stack.c
queue.o :       queue.c
	$(CC) $(CFLAGS) -c queue.c
clean   :
	rm -f $(OBJECTS) decode 
