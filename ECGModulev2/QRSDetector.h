#pragma once

#include <stdio.h>

#include "ECGPkg.h"

/*
 * Class QRSDetector. 
 */
typedef struct QRSDetector QRSDetector;

struct QRSDetector
{
	int heartRate;
	struct TMDQueue* itsTMDQueue;
};

/*
 * Constructors and destructors. 
 */
void QRSDetector_Init(QRSDetector* const me);
void QRSDetector_Cleanup(QRSDetector* const me);

void QRSDetector_update(QRSDetector* const me, const struct TimeMarkedData tmd);

/*
 * Operations. 
 */
void QRSDetector_computeHR(QRSDetector* const me);
void QRSDetector_getDataSample(QRSDetector* const me);

struct TMDQueue* QRSDetector_getItsTMDQueue(QRSDetector* const me);
void QRSDetector_setItsTMDQeue(QRSDetector* const me, struct TMDQueue* p_TMDQueue);

QRSDetector* QRSDetector_Create(void);
void QRSDetector_Destroy(QRSDetector* const me);