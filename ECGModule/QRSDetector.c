#include <stdlib.h>

#include "QRSDetector.h"
#include "TMDQueue.h"

static void cleanUpRelations(QRSDetector* const me);

void QRSDetector_Init(QRSDetector* const me)
{
	me->heartRate = 0;
	me->index = 0;
	me->itsTMDQueue = NULL;
}

void QRSDetector_Cleanup(QRSDetector* const me)
{
	cleanUpRelations(me);
}

void QRSDetector_computeHR(QRSDetector* const me)
{
	/*
	 * Do the right stuff here... 
	 */
}

void QRSDetector_getDataSample(QRSDetector* const me)
{
	TimeMarkedData tmd;

	tmd = TMDQueue_remove(me->itsTMDQueue, me->index);

	printf("\tQRS index: %d TimeInterval: %d DataValue: %d\n",
		me->index, tmd.timeInterval, tmd.dataValue);

	me->heartRate = tmd.dataValue;

	/*
	 * Might have to do additional things here...
	 */

	me->index = TMDQueue_getNextIndex(me->itsTMDQueue, me->index);
}

TMDQueue* QRSDetector_getItsTMDQueue(QRSDetector* const me)
{
	return me->itsTMDQueue;
}

void QRSDetector_setItsTMDQeue(QRSDetector* const me, TMDQueue* p_TMDQueue)
{
	me->itsTMDQueue = p_TMDQueue;
}

QRSDetector* QRSDetector_Create(void)
{
	QRSDetector* me = (QRSDetector*)malloc(sizeof(QRSDetector));
	if (me != NULL)
		QRSDetector_Init(me);

	return me;
}

void QRSDetector_Destroy(QRSDetector* const me)
{
	if (me != NULL)
		cleanUpRelations(me);
	free(me);
}

static void cleanUpRelations(QRSDetector* const me)
{
	me->itsTMDQueue = NULL;
}