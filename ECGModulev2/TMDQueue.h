#pragma once
/*
 * This queue holds the data inserted by the ECG_module for its various clients 
 */
#include <stdio.h>

#include "ECGPkg.h"
#include "TimeMarkedData.h"

struct NotificationHandle;

/*
 * This queue is meant to operate as a "leaky" queue. In this queue, data are
 * never removed per se, but are instead overwritten when the buffer pointer
 * wraps around. This allows for many clients to read the same data from it.
 */
typedef struct TMDQueue TMDQueue;

struct TMDQueue
{
	int head;
	int size;
	int nSubscribers;
	struct TimeMarkedData buffer[QUEUE_SIZE];
	struct NotificationHandle* itsNotificationHandle;
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

/*
 * Used to notify the subscribers about the availability of new data. 
 */
void TMDQueue_notify(TMDQueue* const me, const struct TimeMarkedData tmd);
/*
 * The notification handle is managed as a linked list, with insertion at the end. 
 */
void TMDQueue_subscribe(TMDQueue* const me, const UpdateFuncPtr updateFuncAddr);
int TMDQueue_unsubscribe(TMDQueue* const me, const UpdateFuncPtr updateFuncAddr);
struct NotificationHandle* TMDQueue_getItsNotificationHandle(TMDQueue* const me);
void TMDQueue_setItsNotificationHandle(TMDQueue* const me,
	struct NotificationHandle* p_NotificationHandle);

int TMDQueue_getBuffer(TMDQueue* const me);
TMDQueue* TMDQueue_Create(void);
void TMDQueue_Destroy(TMDQueue* const me);