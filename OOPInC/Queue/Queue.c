/**
 * Queue.c:
 * ========
 * 
 * Implementation of a Queue in an OOP fashion in C.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

void Queue_Init(
	Queue* const me,
	int (*isFullfunction)(Queue* const me),
	int (*isEmptyfunction)(Queue* const me),
	int (*getSizefunction)(Queue* const me),
	void (*insertfunction)(Queue* const me, int k),
	int (*removefunction)(Queue* const me)
)
{
	/*
	 * Attribute initialization. 
	 */
	me->head = 0;
	me->size = 0;
	me->tail = 0;

	/*
	 * Member function initialization. 
	 */
	me->isFull = isFullfunction;
	me->isEmpty = isEmptyfunction;
	me->getSize = getSizefunction;
	me->insert = insertfunction;
	me->remove = removefunction;
}

void Queue_Cleanup(Queue* const me)
{
}

int Queue_getSize(Queue* const me)
{
	return me->size;
}

int Queue_isEmpty(Queue* const me)
{
	return Queue_getSize(me) == 0;
}

int Queue_isFull(Queue* const me)
{
	return me->getSize(me) == QUEUE_SIZE;
}

void Queue_insert(Queue* const me, int k)
{
	if (!me->isFull(me))
	{
		me->buffer[me->head] = k;
		me->head = (me->head + 1) % QUEUE_SIZE;
		++(me->size);
	}
}

int Queue_remove(Queue* const me)
{
	int value = -9999;

	if (!me->isEmpty(me))
	{
		value = me->buffer[me->tail];
		me->tail = (me->tail + 1) % QUEUE_SIZE;
		--(me->size);
	}

	return value;
}

Queue* Queue_Create(void)
{
	Queue* me = (Queue*)malloc(sizeof(Queue));
	if (me != NULL)
	{
		Queue_Init(me, Queue_isFull, Queue_isEmpty,
			Queue_getSize, Queue_insert, Queue_remove);
	}

	return me;
}

void Queue_Destroy(Queue* const me)
{
	if (me != NULL)
	{
		Queue_Cleanup(me);
	}

	free(me);
}