# include "stack.h"
# include <stdio.h>
# include <stdlib.h>

stack *newStack()
{
	stack *s = (stack *) malloc(sizeof(stack));
	s -> size = 0;
	s -> top = 0;
	s -> entries = calloc(0, sizeof(item));
	return s;
}

void delStack(stack *s)
{
	free(s -> entries);
	free(s);
	return;
}

bool empty(stack *s)
{
	if (s -> top == 0)
	{
		return true;
	}
	return false;
}

bool full(stack *s)
{
	if (s -> size == s -> top)
	{
		return true;
	}
	return false;
}

item pop(stack *s)
{
	return s -> entries[(s -> top)--]; 
}

void push(stack *s, item i)
{
	if (s -> size == 0)
	{
		(s -> size)++;
		s -> entries = realloc(s -> entries, (s -> size)*(sizeof(item)));
	}
	else if (full(s))
	{
		(s -> size) *= 2;
		s -> entries = realloc(s -> entries, (s -> size)*(sizeof(item))); 
	}
	s -> entries[(s -> top)++] = i;
	return;
}

void printStack(stack *s)
{
	for (uint32_t i = 0; i < s -> top; i++)
	{
		printf("%u\t", s -> entries[i]);
	}
	printf("\n");
}
/*
int main()
{
	stack *s = newStack();
	push(s, 1);
	push(s, 2);
	push(s, 3);
	pop(s);
	push(s, 4);
        push(s, 5);
        push(s, 6);
	push(s, 7);
        push(s, 8);
        push(s, 9);
	push(s, 10);

	printf("Size: %u\nTop: %u\n", s -> size, s -> top);
	printStack(s);
	delStack(s);
}
*/
