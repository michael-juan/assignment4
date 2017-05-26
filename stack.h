# ifndef _STACK_H
# define _STACK_H
# include <stdint.h>
# include <stdbool.h>

typedef uint32_t item; 

typedef struct stack
{
	uint32_t size;
	uint32_t top;
	item *entries;
} stack;

stack *newStack();

void delStack(stack *stack);

item pop(stack *stack);

void push(stack *stack, item);

bool empty(stack *stack);

bool full(stack *stack);

# endif
