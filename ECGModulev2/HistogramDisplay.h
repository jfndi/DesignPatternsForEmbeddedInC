#pragma once
#include <stdio.h>

#include "ECGPkg.h"

/*
 * Class HistogramDisplay. 
 */
typedef struct HistogramDisplay HistogramDisplay;

struct HistogramDisplay
{
	struct TMDQueue* itsTMDQueue;
};

/*
 * Constructors and destructors. 
 */
void HistogramDisplay_Init(HistogramDisplay* const me);
void HistogramDisplay_Cleanup(HistogramDisplay* const me);

void HistogramDisplay_update(HistogramDisplay* const me, const struct TimeMarkedData tmd);

/*
 * Operations. 
 */
void HistogramDisplay_updateHistogram(HistogramDisplay* const me);

struct TMDQueue* HistogramDisplay_getItsTMDQueue(HistogramDisplay* const me);
void HistogramDisplay_setItsTMDQueue(HistogramDisplay* const me,
	struct TMDQueue* p_TMDQueue);

HistogramDisplay* HistogramDisplay_Create(void);
void HistogramDisplay_Destroy(HistogramDisplay* const me);