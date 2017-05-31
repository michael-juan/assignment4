CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99 -g
OBJECTS = queue.o

.PHONY  :       all     clean

all     :       testing
testing :       $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o testing
stack.o :       stack.c
	$(CC) $(CFLAGS) -c stack.c
queue.o :       queue.c
	$(CC) $(CFLAGS) -c queue.c
clean   :
	rm -f $(OBJECTS) testing
