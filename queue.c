# include "queue.h"
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
//make the priority queue 256*3 in when implementing 
void swap(queue *q, uint32_t indexOne, uint32_t indexTwo)
{
	treeNode *temp = q -> Q[indexOne];
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
			if ((q -> Q[tracker]) -> count < (q -> Q[i-1]) -> count)
			{
				swap(q, i-1, tracker);
                		tracker = i-1;
			}
		}
	}

	(q -> head)++;
	return true;

}

/* Help from Art on 5/30/17 */
