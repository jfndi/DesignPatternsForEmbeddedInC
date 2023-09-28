#pragma once

#include <stdio.h>

#include "ECGPkg.h"
#include "NotificationHandle.h"
#include "ArrythmiaDetector.h"
#include "ECG_Module.h"
#include "HistogramDisplay.h"
#include "QRSDetector.h"
#include "TMDQueue.h"
#include "WaveformDisplay.h"

/*
 * Class TestBuilder. 
 */
typedef struct TestBuilder TestBuilder;

struct TestBuilder
{
	struct ArrythmiaDetector itsArrythmiaDetector;
	struct ECG_Module itsECG_Module;
	struct HistogramDisplay itsHistogramDisplay;
	struct QRSDetector itsQRSDetector;
	struct TMDQueue itsTMDQueue;
	struct WaveformDisplay itsWaveformDisplay;
};

/*
 * Constructors and destructors. 
 */
void TestBuilder_Init(TestBuilder* const me);
void TestBuilder_Cleanup(TestBuilder* const me);

struct ArrythmiaDetector* TestBuilder_getItsArrythmiaDetector(TestBuilder* const me);
struct ECG_Module* TestBuilder_getItsECG_Module(TestBuilder* const me);
struct HistogramDisplay* TestBuilder_getItsHistogramDisplay(TestBuilder* const me);
struct QRSDetector* TestBuilder_getItsQRSDetector(TestBuilder* const me);
struct TMDQueue* TestBuilder_getItsTMDQueue(TestBuilder* const me);
struct WaveformDisplay* TestBuilder_getItsWaveformDisplay(TestBuilder* const me);

TestBuilder* TestBuilder_Create(void);
void TestBuilder_Destroy(TestBuilder* const me);
void TestBuilder_Destroy(TestBuilder* const me);