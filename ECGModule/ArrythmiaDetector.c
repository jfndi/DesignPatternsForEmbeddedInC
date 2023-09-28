#include <stdlib.h>

#include "ArrythmiaDetector.h"

#include "TMDQueue.h"

static void cleanUpRelations(ArrythmiaDetector* const me);

void ArrythmiaDetector_Init(ArrythmiaDetector* const me)
{
	me->index = 0;
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

void ArrythmiaDetector_identifyArrythmia(ArrythmiaDetector* const me)
{
	/*
	 * Do the right thing here... 
	 */
}

void ArrythmiaDetector_getDataSample(ArrythmiaDetector* const me)
{
	TimeMarkedData tmd;

	tmd = TMDQueue_remove(me->itsTMDQueue, me->index);

	printf("\tArrythmia index: %d TimeInterval: %d DataValue: %d\n",
		me->index, tmd.timeInterval, tmd.dataValue);

	/*
	 * Might have to do additional things here... 
	 */

	me->index = TMDQueue_getNextIndex(me->itsTMDQueue, me->index);
}

struct TMDQueue* ArrythmiaDetector_getItsTMDQueue(ArrythmiaDetector* const me)
{
	return me->itsTMDQueue;
}

void ArrythmiaDetector_setItsTMDQueue(ArrythmiaDetector* const me, TMDQueue* p_TMDQueue)
{
	me->itsTMDQueue = p_TMDQueue;
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
	me->itsTMDQueue = NULL;
}