#pragma once
#include <stdio.h>

/*
 * Forward declarations. 
 */
struct ArrytmiaDetector;
struct ECG_Module;
struct HistogramDisplay;
struct QRSDetector;
struct TMDQueue;
struct TestBuilder;
struct TimeMarkedData;
struct WaveformDisplay;

typedef unsigned char boolean;

#define QUEUE_SIZE	(20000)