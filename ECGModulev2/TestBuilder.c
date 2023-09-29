#include <stdlib.h>

#include "TestBuilder.h"

static void initRelations(TestBuilder* const me);
static void cleanUpRelations(TestBuilder* const me);

void TestBuilder_Init(TestBuilder* const me)
{
	initRelations(me);
}

void TestBuilder_Cleanup(TestBuilder* const me)
{
	cleanUpRelations(me);
}

struct ArrythmiaDetector* TestBuilder_getItsArrythmiaDetector(TestBuilder* const me)
{
	return &me->itsArrythmiaDetector;
}

struct ECG_Module* TestBuilder_getItsECG_Module(TestBuilder* const me)
{
	return &me->itsECG_Module;
}

struct HistogramDisplay* TestBuilder_getItsHistogramDisplay(TestBuilder* const me)
{
	return &me->itsHistogramDisplay;
}

struct QRSDetector* TestBuilder_getItsQRSDetector(TestBuilder* const me)
{
	return &me->itsQRSDetector;
}

struct TMDQueue* TestBuilder_getItsTMDQueue(TestBuilder* const me)
{
	return &me->itsTMDQueue;
}

struct WaveformDisplay* TestBuilder_getItsWaveformDisplay(TestBuilder* const me)
{
	return &me->itsWaveformDisplay;
}

TestBuilder* TestBuilder_Create(void)
{
	TestBuilder* me = (TestBuilder*)malloc(sizeof(TestBuilder));
	if (me != NULL)
		TestBuilder_Init(me);
	return me;
}

void TestBuilder_Destroy(TestBuilder* const me)
{
	if (me != NULL)
		TestBuilder_Cleanup(me);
	free(me);
}

static void initRelations(TestBuilder* const me)
{
	ArrythmiaDetector_Init(&me->itsArrythmiaDetector);
	ECG_Module_Init(&me->itsECG_Module);
	HistogramDisplay_Init(&me->itsHistogramDisplay);
	QRSDetector_Init(&me->itsQRSDetector);
	TMDQueue_Init(&me->itsTMDQueue);
	WaveformDisplay_Init(&me->itsWaveformDisplay);

	ECG_Module_setItsTMDQueue(&me->itsECG_Module, &me->itsTMDQueue);
	ArrythmiaDetector_setItsTMDQueue(&me->itsArrythmiaDetector, &me->itsTMDQueue);
	HistogramDisplay_setItsTMDQueue(&me->itsHistogramDisplay, &me->itsTMDQueue);
	QRSDetector_setItsTMDQeue(&me->itsQRSDetector, &me->itsTMDQueue);
	WaveformDisplay_setItsTMDQueue(&me->itsWaveformDisplay, &me->itsTMDQueue);
}

static void cleanUpRelations(TestBuilder* const me)
{
	ArrythmiaDetector_Cleanup(&me->itsArrythmiaDetector);
	ECG_Module_Cleanup(&me->itsECG_Module);
	HistogramDisplay_Cleanup(&me->itsHistogramDisplay);
	QRSDetector_Cleanup(&me->itsQRSDetector);
	WaveformDisplay_Cleanup(&me->itsWaveformDisplay);
	/*
	 * Has to be the last as me->itsNotificationHandle will
	 * be set to NULL.
	 */
	TMDQueue_Cleanup(&me->itsTMDQueue);
}