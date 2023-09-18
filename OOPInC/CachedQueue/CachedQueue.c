#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CachedQueue.h"

void CachedQueue_Init(
	CachedQueue* me,
	char* fName,
	int (*isFullfunction)(CachedQueue* const me),
	int (*isEmptyfunction)(CachedQueue* const me),
	int (*getSizefunction)(CachedQueue* const me),
	void (*insertfunction)(CachedQueue* const me, int k),
	int (*removefunction)(CachedQueue* const me),
	void (*flushfunction)(CachedQueue* const me),
	void (*loadfunction)(CachedQueue* const me)
)
{
	/*
	 * Initialize base class.
	 */
	me->queue = Queue_Create();

	/*
	 * Initialize subclass attributes. 
	 */
	me->numberOfElementsOnDisk = 0;
	strcpy_s(me->filename, sizeof(me->filename), fName);

	/*
	 * Initialize aggregate. 
	 */
	me->outputQueue = Queue_Create();

	/*
	 * Initialize subclass virtual operations.
	 */
	me->isFull = isFullfunction;
	me->isEmpty = isEmptyfunction;
	me->getSize = getSizefunction;
	me->insert = insertfunction;
	me->remove = removefunction;
	me->flush = flushfunction;
	me->load = loadfunction;
}

/*
 * Operation cleanup. 
 */
void CachedQueue_Cleanup(CachedQueue* const me)
{
	Queue_Cleanup(me->queue);
}

/*
 * Operation isFull. 
 */
int CachedQueue_isFull(CachedQueue* const me)
{
	return me->queue->isFull(me->queue) && me->outputQueue->isFull(me->outputQueue);
}

/*
 * Operation isEmpty. 
 */
int CachedQueue_isEmpty(CachedQueue* const me)
{
	return me->queue->isEmpty(me->queue) &&
		me->outputQueue->isEmpty(me->outputQueue) &&
		(me->numberOfElementsOnDisk == 0);
}

/*
 * Operation getSize. 
 */
int CachedQueue_getSize(CachedQueue* const me)
{
	return me->queue->getSize(me->queue) +
		me->outputQueue->getSize(me->outputQueue) +
		me->numberOfElementsOnDisk;
}

/*
 * Operation instert. 
 */
void CachedQueue_insert(CachedQueue* const me, int k)
{
	if (me->queue->isFull(me->queue))
		me->flush(me);
	me->queue->insert(me->queue, k);
}

/*
 * Operation remove. 
 */
int CachedQueue_remove(CachedQueue* const me)
{
	if (!me->outputQueue->isEmpty(me->outputQueue))
		return me->outputQueue->remove(me->outputQueue);
	else if (me->numberOfElementsOnDisk > 0)
	{
		me->load(me);
		return me->outputQueue->remove(me->outputQueue);
	}
	else
		return me->queue->remove(me->queue);
}

/*
 * Operation flush.
 *
 * Algorithm:
 *	- if file not open, then open it
 *  - while not queue->isEmpty: queue->remove; write data to disk; increment number of elements.
 */
void CachedQueue_flush(CachedQueue* const me)
{
	//TODO.
}

/*
 * Operation load.
 * 
 * Algorithm:
 * - while (!outputQueue->isFull() && numberOfElementsOnDisk > 0
 *		read from start of file
 *		numberElementOndisk--;
 *		outputQueue->insert()
 */
void CachedQueue_load(CachedQueue* const me)
{
	//TODO.
}

CachedQueue* CachedQueue_Create(void)
{
	CachedQueue* me = (CachedQueue*)malloc(sizeof(CachedQueue));
	if (me != NULL)
	{
		CachedQueue_Init(me, "C:/Users/Kyria/queuebuffer.dat",
			CachedQueue_isFull, CachedQueue_isEmpty, CachedQueue_getSize,
			CachedQueue_insert, CachedQueue_remove, CachedQueue_flush, CachedQueue_load);
	}

	return me;
}

CachedQueue_Destroy(CachedQueue* const me)
{
	if (me != NULL)
		CachedQueue_Cleanup(me);

	free(me);
}

int main(void)
{
	// TODO: Unit tests.
	return EXIT_SUCCESS;
}