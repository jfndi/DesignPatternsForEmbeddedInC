#include <stdlib.h>

#include "NotificationHandle.h"
#include "ArrythmiaDetector.h"

#include "TMDQueue.h"

static void cleanUpRelations(ArrythmiaDetector* const me);

void ArrythmiaDetector_Init(ArrythmiaDetector* const me)
{
	me->fibrillation = 0;
	me->firstDegreeHeatBlock = 0;
	me->prematureAtrialContraction = 0;
	me->pvcCount = 0;
	me->STSegmentHeight = 0;
	me->Two_one_heartBlock = 0;
	me->itsTMDQueue = NULL;
}

void ArrythmiaDetector_Cleanup(ArrythmiaDetector* const me)
{
	cleanUpRelations(me);
}

void ArrythmiaDetector_update(ArrythmiaDetector* const me, const TimeMarkedData tmd)
{
	printf("\tArrythmia TimeInterval: %d DataValue: %d\n",
		tmd.timeInterval, tmd.dataValue);
}

void ArrythmiaDetector_identifyArrythmia(ArrythmiaDetector* const me)
{
	/*
	 * Do the right thing here... 
	 */
}

struct TMDQueue* ArrythmiaDetector_getItsTMDQueue(ArrythmiaDetector* const me)
{
	return me->itsTMDQueue;
}

void ArrythmiaDetector_setItsTMDQueue(ArrythmiaDetector* const me, TMDQueue* p_TMDQueue)
{
	me->itsTMDQueue = p_TMDQueue;
	TMDQueue_subscribe(me->itsTMDQueue, ArrythmiaDetector_update);
}

ArrythmiaDetector* ArrythmiaDetector_Create(void)
{
	ArrythmiaDetector* me = (ArrythmiaDetector*)malloc(sizeof(ArrythmiaDetector));
	if (me != NULL)
		ArrythmiaDetector_Init(me);

	return me;
}

void ArrythmiaDetector_Destroy(ArrythmiaDetector* const me)
{
	if (me != NULL)
		ArrythmiaDetector_Cleanup(me);
	free(me);
}

static void cleanUpRelations(ArrythmiaDetector* const me)
{
	TMDQueue_unsubscribe(me->itsTMDQueue, ArrythmiaDetector_update);
	me->itsTMDQueue = NULL;
}