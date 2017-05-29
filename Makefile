CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99 -g
OBJECTS = stack.o

.PHONY	:	all	clean

all	:	stack
stack.o	:	stack.c
	$(CC) $(CFLAGS) -c stack.c
clean	:
	rm -f $(OBJECTS) stack
