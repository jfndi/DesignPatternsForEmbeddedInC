#pragma once
#include <stdio.h>

#include "ECGPkg.h"

/*
 * Class ArrythmiaDetector.
 */
typedef struct ArrythmiaDetector ArrythmiaDetector;

struct ArrythmiaDetector
{
	int pvcCount;
	int STSegmentHeight;
	int firstDegreeHeatBlock;
	int Two_one_heartBlock;
	int prematureAtrialContraction;
	int fibrillation;
	int index;

	struct TMDQueue* itsTMDQueue;
};

/*
 * Constructors and destructors. 
 */
void ArrythmiaDetector_Init(ArrythmiaDetector* const me);
void ArrythmiaDetector_Cleanup(ArrythmiaDetector* const me);

/*
 * Operations. 
 */
void ArrythmiaDetector_identifyArrythmia(ArrythmiaDetector* const me);
void ArrythmiaDetector_getDataSample(ArrythmiaDetector* const me);

struct TMDQueue* ArrythmiaDetector_getItsTMDQueue(ArrythmiaDetector* const me);
void ArrythmiaDetector_setItsTMDQueue(ArrythmiaDetector* const me, struct TMDQueue* p_TMDQueue);

ArrythmiaDetector* ArrythmiaDetector_Create(void);
void ArrythmiaDetector_Destroy(ArrythmiaDetector* const me);