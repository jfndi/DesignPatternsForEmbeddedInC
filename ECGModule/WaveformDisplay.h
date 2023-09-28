#pragma once
#include <stdio.h>

#include "ECGPkg.h"

/*
 * Class WaveformDisplay.
 */
typedef struct WaveformDisplay WaveformDisplay;

struct WaveformDisplay
{
	int index;
	struct TMDQueue* itsTMDQueue;
};

/*
 * Constructors and destructors.
 */
void WaveformDisplay_Init(WaveformDisplay* const me);
void WaveformDisplay_Cleanup(WaveformDisplay* const me);

/*
 * Operations.
 */
void WaveformDisplay_display(WaveformDisplay* const me);
void WaveformDisplay_getScalarValue(WaveformDisplay* const me);

struct TMDQueue* WaveformDisplay_getItsTMDQueue(WaveformDisplay* const me);
void WaveformDisplay_setItsTMDQueue(WaveformDisplay* const me, struct TMDQueue* p_TMDQueue);

WaveformDisplay* WaveformDisplay_Create(void);
void WaveformDisplay_Destroy(WaveformDisplay* const me);