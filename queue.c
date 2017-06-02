# include "queue.h"
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>

void swap(queue *q, uint32_t indexOne, uint32_t indexTwo)
{
	uint32_t temp = q -> Q[indexOne];
        q -> Q[indexOne] = q -> Q[indexTwo];
        q -> Q[indexTwo] = temp;
	return;
}

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

bool dequeue(queue *q, item *i)
{
	if (empty(q))
	{
		return false; 
	}	
	*i = q -> Q[q -> tail];
	(q -> tail)++;
	return true;
}

bool enqueue(queue *q, item i)
{
	if (full(q))
	{
		return false;
	}
	uint32_t tracker = (q -> head);
	
	q -> Q[q -> head] = i;	
	if (q -> head > 0)
	{
		for (uint32_t i = tracker; i > (q -> tail); i--)
		{	
			if (q -> Q[tracker] < q -> Q[i-1])
			{
				swap(q, i-1, tracker);
                		tracker = i-1;
			}
		}
	}

	(q -> head)++;
	return true;

}

void printQueue(queue *q)
{		
	for (uint32_t i = q -> tail; i < q -> head; i++)
	{
		printf("%u\t", q -> Q[i]);
	}
	printf("\n");
}
/*
int main(void)
{
	queue *q = newQueue(20);
	uint32_t a = 500;
	enqueue(q, 3);
	enqueue(q, 5);
	enqueue(q, 4);
	enqueue(q, 8);
	enqueue(q, 2);
	dequeue(q, &a);
	enqueue(q, 1);
	enqueue(q, 50);
	enqueue(q, 49);
	dequeue(q, &a);
	enqueue(q, 9);
	enqueue(q, 11);
	enqueue(q, 17);
	enqueue(q, 22);
	dequeue(q, &a);
	printQueue(q);
	delQueue(q);
	return 0;
}
*/
/* Help from Art on 5/30/17 */
