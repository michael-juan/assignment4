# include "queue.h"
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>

queue *newQueue(uint32_t qSize)
{
	queue *q = (queue *) malloc(sizeof(queue));
	q -> size = qSize;
	q -> Q = calloc(qSize, sizeof(item));
	q -> head = 0;
	q -> tail = 0; 
	return q;	
}

void delQueue(queue *q)
{
	free(q -> Q);
	free(q);
	return;
}

bool empty(queue *q)
{
	if (q -> tail == q -> head)
	{
		return true;
	}	
	return false;
}

bool full(queue *q)
{
	if (q -> head == q -> size)
	{
		return true;
	}
	return false;
}
/*
bool dequeue(queue *q, item *i)
{
		
}
*/
bool enqueue(queue *q, item i)
{
	q -> Q[q -> head] = i;
	(q -> head)++;
	return true;
}

void printQueue(queue *q)
{
	for (uint32_t i = 0; i < q -> size; i++)
	{
		printf("%u\t", q -> Q[i]);
	}
	printf("\n");
	return;
}

int main(void)
{
	printf("hi");
	queue *q = newQueue(5);
	enqueue(q, 3);
	enqueue(q, 4);
	enqueue(q, 5);
	enqueue(q, 6);
	printQueue(q);
	return 0;
}

/* Help from Art on 5/30/17 */
