#pragma once
/*
 * This queue holds the data inserted by the ECG_module for its various clients 
 */
#include <stdio.h>

#include "ECGPkg.h"
#include "TimeMarkedData.h"

typedef struct TMDQueue TMDQueue;

/*
 * This queue is meant to operate as a "leaky" queue. In this queue, data are
 * never removed per se, but are instead overwritten when the buffer pointer
 * wraps around. This allows for many clients to read the same data from it.
 */
struct TMDQueue
{
	int head;
	int size;
	struct TimeMarkedData buffer[QUEUE_SIZE];
};

/*
 * Constructors and destructors. 
 */
void TMDQueue_Init(TMDQueue* const me);
void TMDQueue_Cleanup(TMDQueue* const me);

/*
 * Operations. 
 */
int TMDQueue_getNextIndex(TMDQueue* const me, int index);
void TMDQueue_insert(TMDQueue* const me, const struct TimeMarkedData tmd);
boolean TMDQueue_isEmpty(TMDQueue* const me);
struct TimeMarkedData TMDQueue_remove(TMDQueue* const me, int index);
int TMDQueue_getBuffer(TMDQueue* const me);
TMDQueue* TMDQueue_Create(void);
void TMDQueue_Destroy(TMDQueue* const me);