#pragma once

#include <stdio.h>
#include "ECGPkg.h"

typedef void(*UpdateFuncPtr)(void* const me, const struct TimeMarkedData tm);

typedef struct NotificationHandle NotificationHandle;

struct NotificationHandle
{
	UpdateFuncPtr updateAddr;
	struct NotificationHandle* itsNotificationHandle;
};

/*
 * Constructors destructors. 
 */
void NotificationHandle_Init(NotificationHandle* const me);
void NotificationHandle_Cleanup(NotificationHandle* const me);

NotificationHandle* NotificationHandle_getItsNotificationHandle(
	NotificationHandle* const me);
void NotificationHandle_setItsNotificationHandle(NotificationHandle*
	const me, NotificationHandle* p_NotificationHandle);

NotificationHandle* NotificationHandle_Create(void);
void NotificationHandle_Destroy(NotificationHandle* const me);