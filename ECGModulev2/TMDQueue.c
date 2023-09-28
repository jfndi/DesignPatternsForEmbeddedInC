#include <stdlib.h>

#include "NotificationHandle.h"
#include "TMDQueue.h"

static void initRelations(TMDQueue* const me);
static void cleanUpRelations(TMDQueue* const me);

void TMDQueue_Init(TMDQueue* const me)
{
	me->head = 0;
	me->size = 0;
	me->nSubscribers = 0;
	me->itsNotificationHandle = NULL;
	initRelations(me);
}

void TMDQueue_Cleanup(TMDQueue* const me)
{
	cleanUpRelations(me);
}

/*
 * Operation getNextIndex(int). 
 */
int TMDQueue_getNextIndex(TMDQueue* const me, int index)
{
	return (index + 1) % QUEUE_SIZE;
}

/*
 * Operation insert(TimeMarkedData). 
 */
void TMDQueue_insert(TMDQueue* const me, const struct TimeMarkedData tmd)
{
	printf("Inserting at: %d Data #: %d", me->head, tmd.timeInterval);
	me->buffer[me->head] = tmd;
	me->head = TMDQueue_getNextIndex(me, me->head);
	if (me->size < QUEUE_SIZE)
		++me->size;
	printf(" Storing data value: %d\n", tmd.dataValue);
	TMDQueue_notify(me, tmd);
}

/*
 * Operation isEmpty(). 
 */
boolean TMDQueue_isEmpty(TMDQueue* const me)
{
	return (boolean)(me->size == 0);
}

/*
 * Operation remove(int). 
 */
struct TimeMarkedData TMDQueue_remove(TMDQueue* const me, int index)
{
	TimeMarkedData tmd;

	tmd.timeInterval = -1;
	tmd.dataValue = -9999;

	if (!TMDQueue_isEmpty(me) && (index >= 0) && (index < QUEUE_SIZE)
		&& (index < me->size))
		tmd = me->buffer[index];

	return tmd;
}

void TMDQueue_notify(TMDQueue* const me, const TimeMarkedData tmd)
{
	struct NotificationHandle* pNH;

	pNH = me->itsNotificationHandle;
	while (pNH)
	{
		printf("---->> calling updateAdd on pNH %p\n", pNH);
		pNH->updateAddr(NULL, tmd);
		pNH = pNH->itsNotificationHandle;
	}
}

void TMDQueue_subscribe(TMDQueue* const me, const UpdateFuncPtr updateFuncAddr)
{
	struct NotificationHandle* pNH;

	pNH = me->itsNotificationHandle;
	if (pNH == NULL)
	{
		printf("---->> Added to a new list\n");
		me->itsNotificationHandle = NotificationHandle_Create();
		printf("---->> Called NH_Create()\n");
		pNH = me->itsNotificationHandle;
	}
	else
	{
		printf("---->> Adding to an existing list\n");
		while (pNH->itsNotificationHandle != NULL)
		{
			printf("---->> Getting ready  to augment ptr %p to %p\n", pNH, pNH->itsNotificationHandle);
			pNH = pNH->itsNotificationHandle;
			printf("---->> Augmenting ptr\n");
		}
		printf("---->> Calling NH_Create()\n");
		pNH->itsNotificationHandle = NotificationHandle_Create();
		pNH = pNH->itsNotificationHandle;
	}

	pNH->updateAddr = updateFuncAddr;
	++me->nSubscribers;
}

int TMDQueue_unsubscribe(TMDQueue* const me, const UpdateFuncPtr updateFuncAddr)
{
	struct NotificationHandle* pNH;
	struct NotificationHandle* pPrevious;

	pNH = pPrevious = me->itsNotificationHandle;
	if (pNH == NULL)
	{
		return 0;
	}
	else
	{
		printf("---->> Searching...\n");
		while (pNH != NULL)
		{
			if (pNH->updateAddr != updateFuncAddr)
			{
				pPrevious = pNH;
				pNH = pNH->itsNotificationHandle;
			}
			else
			{
				if (pPrevious == pNH)
				{
					pPrevious = pNH->itsNotificationHandle;
					me->itsNotificationHandle = pPrevious;
				}
				else
					pPrevious->itsNotificationHandle = pNH->itsNotificationHandle;
				free(pNH);
				--me->nSubscribers;
				return 1;
			}
		}
	}
	return 0;
}

struct NotificationHandle* TMDQueue_getItsNotificationHandle(TMDQueue* const me)
{
	return me->itsNotificationHandle;
}

void TMDQueue_setItsNotificationHandle(TMDQueue* const me, NotificationHandle* p_NotificationHandle)
{
	me->itsNotificationHandle = p_NotificationHandle;
}

int TMDQueue_getBuffer(TMDQueue* const me)
{
	int iter = 0;

	return iter;
}

struct TMDQueue* TMDQueue_Create(void)
{
	TMDQueue* me = (TMDQueue*)malloc(sizeof(TMDQueue));
	if (me != NULL)
		TMDQueue_Init(me);

	return me;
}

void TMDQueue_Destroy(TMDQueue* const me)
{
	if (me != NULL)
		TMDQueue_Cleanup(me);

	free(me);
}

static void initRelations(TMDQueue* const me)
{
	int iter = 0;
	while (iter < QUEUE_SIZE)
	{
		TimeMarkedData_Init(&(me->buffer)[iter]);
		TimeMarkedData__setItsTMDQueue(&(me->buffer)[iter], me);
		iter++;
	}
}

static void cleanUpRelations(TMDQueue* const me)
{
	int iter = 0;

	while (iter < QUEUE_SIZE)
	{
		TimeMarkedData_Cleanup(&(me->buffer)[iter]);
		iter++;
	}

	me->itsNotificationHandle = NULL;
}