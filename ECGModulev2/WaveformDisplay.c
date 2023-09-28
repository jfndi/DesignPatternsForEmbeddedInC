#include <stdlib.h>

#include "WaveformDisplay.h"
#include "NotificationHandle.h"
#include "TMDQueue.h"

static void cleanUpRelations(WaveformDisplay* const me);

void WaveformDisplay_Init(WaveformDisplay* const me)
{
	me->itsTMDQueue = NULL;
}

void WaveformDisplay_Cleanup(WaveformDisplay* const me)
{
	cleanUpRelations(me);
}

void WaveformDisplay_update(WaveformDisplay* const me, const TimeMarkedData tmd)
{
	printf("\tWaveform TimeInterval: %d DataValue: %d\n",
		tmd.timeInterval, tmd.dataValue);
}

void WaveformDisplay_display(WaveformDisplay* const me)
{
	/*
	 * Do the required stuff here... 
	 */
}

struct TMDQueue* WaveformDisplay_getItsTMDQueue(WaveformDisplay* const me)
{
	return me->itsTMDQueue;
}

void WaveformDisplay_setItsTMDQueue(WaveformDisplay* const me, struct TMDQueue* p_TMDQueue)
{
	me->itsTMDQueue = p_TMDQueue;
	TMDQueue_subscribe(me->itsTMDQueue, WaveformDisplay_update);
}

WaveformDisplay* WaveformDisplay_Create(void)
{
	WaveformDisplay* me = (WaveformDisplay*)malloc(sizeof(WaveformDisplay));
	if (me != NULL)
		WaveformDisplay_Init(me);
	return me;
}

void WaveformDisplay_Destroy(WaveformDisplay* const me)
{
	if (me != NULL)
		WaveformDisplay_Cleanup(me);
	free(me);
}

static void cleanUpRelations(WaveformDisplay* const me)
{
	TMDQueue_unsubscribe(me->itsTMDQueue, WaveformDisplay_update);
	me->itsTMDQueue = NULL;
}