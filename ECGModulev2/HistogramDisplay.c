#include <stdlib.h>

#include "NotificationHandle.h"
#include "HistogramDisplay.h"
#include "TMDQueue.h"

static void cleanUpRelations(HistogramDisplay* const me);

void HistogramDisplay_Init(HistogramDisplay* const me)
{
	me->itsTMDQueue = NULL;
}

void HistogramDisplay_Cleanup(HistogramDisplay* const me)
{
	cleanUpRelations(me);
}

void HistogramDisplay_update(HistogramDisplay* const me, const TimeMarkedData tmd)
{
	printf("\tHistogram -> TimeInterval: %d DataValue: %d\n", tmd.timeInterval,
		tmd.dataValue);
}

/*
 * Operation updateHistogram(). 
 */
void HistogramDisplay_updateHistogram(HistogramDisplay* const me)
{
	/*
	 * Do the required stuff here... 
	 */
}

struct TMDQueue* HistogramDisplay_getItsTMDQueue(HistogramDisplay* const me)
{
	return me->itsTMDQueue;
}

void HistogramDisplay_setItsTMDQueue(HistogramDisplay* const me, struct TMDQueue* p_TMDQueue)
{
	me->itsTMDQueue = p_TMDQueue;
	TMDQueue_subscribe(me->itsTMDQueue, HistogramDisplay_update);
}

HistogramDisplay* HistogramDisplay_Create(void)
{
	HistogramDisplay* me = (HistogramDisplay*)malloc(sizeof(HistogramDisplay));
	if (me != NULL)
		HistogramDisplay_Init(me);
	return me;
}

void HistogramDisplay_Destroy(HistogramDisplay* const me)
{
	if (me != NULL)
		HistogramDisplay_Cleanup(me);
	free(me);
}

static void cleanUpRelations(HistogramDisplay* const me)
{
	TMDQueue_unsubscribe(me->itsTMDQueue, HistogramDisplay_update);
	me->itsTMDQueue = NULL;
}