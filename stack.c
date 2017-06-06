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

bool stackEmpty(stack *s)
{
	if (s -> top == 0)
	{
		return true;
	}
	return false;
}

bool stackFull(stack *s)
{
	if (s -> size == s -> top)
	{
		return true;
	}
	return false;
}

item pop(stack *s)
{
	if (!stackEmpty(s))
	{
		return s -> entries[--(s -> top)]; 
	}
	return NULL;
}

void push(stack *s, item i)
{
	if (s -> size == 0)
	{
		(s -> size)++;
		s -> entries = realloc(s -> entries, (s -> size)*(sizeof(item)));
	}
	else if (stackFull(s))
	{
		(s -> size) *= 2;
		s -> entries = realloc(s -> entries, (s -> size)*(sizeof(item))); 
	}
	s -> entries[(s -> top)++] = i;
	return;
}
