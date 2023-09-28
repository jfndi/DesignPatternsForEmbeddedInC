#include <stdlib.h>

#include "NotificationHandle.h"
#include "QRSDetector.h"
#include "TMDQueue.h"

static void cleanUpRelations(QRSDetector* const me);

void QRSDetector_Init(QRSDetector* const me)
{
	me->heartRate = 0;
	me->itsTMDQueue = NULL;
}

void QRSDetector_Cleanup(QRSDetector* const me)
{
	cleanUpRelations(me);
}

void QRSDetector_update(QRSDetector* const me, const TimeMarkedData tmd)
{
	printf("\tQRS TimeInterval: %d DataValue: %d\n",
		tmd.timeInterval, tmd.dataValue);
}

void QRSDetector_computeHR(QRSDetector* const me)
{
	/*
	 * Do the right stuff here... 
	 */
}

TMDQueue* QRSDetector_getItsTMDQueue(QRSDetector* const me)
{
	return me->itsTMDQueue;
}

void QRSDetector_setItsTMDQeue(QRSDetector* const me, TMDQueue* p_TMDQueue)
{
	me->itsTMDQueue = p_TMDQueue;
	TMDQueue_subscribe(me->itsTMDQueue, QRSDetector_update);
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
	TMDQueue_unsubscribe(me->itsTMDQueue, QRSDetector_update);
	me->itsTMDQueue = NULL;
}