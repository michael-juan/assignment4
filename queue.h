# ifndef _QUEUE_H
# define _QUEUE_H
# include <stdint.h>
# include <stdbool.h>

typedef uint32_t item;
//at the end, make this a treeNode * item, same with stack.h
typedef struct queue
{
	uint32_t size;
	uint32_t head, tail;
	item *Q;
} queue;

queue *newQueue(uint32_t size);
void delQueue(queue *q);

bool empty(queue *q);
bool full(queue *q);

bool enqueue(queue *q, item i);
bool dequeue(queue *q, item *i);

# endif

