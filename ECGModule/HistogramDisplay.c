#include <stdlib.h>

#include "HistogramDisplay.h"
#include "TMDQueue.h"

static void cleanUpRelations(HistogramDisplay* const me);

void HistogramDisplay_Init(HistogramDisplay* const me)
{
	me->index = 0;
	me->itsTMDQueue = NULL;
}

void HistogramDisplay_Cleanup(HistogramDisplay* const me)
{
	cleanUpRelations(me);
}

/*
 * Operation getValue(). 
 */
void HistogramDisplay_getValue(HistogramDisplay* const me)
{
	TimeMarkedData tmd;

	tmd = TMDQueue_remove(me->itsTMDQueue, me->index);

	printf("\tHistogram index: %d TimeInterval: %d DataValue: %d\n",
		me->index, tmd.timeInterval, tmd.dataValue);

	me->index = TMDQueue_getNextIndex(me->itsTMDQueue, me->index);
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
	me->itsTMDQueue = NULL;
}