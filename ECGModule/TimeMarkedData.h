#pragma once

typedef struct TimeMarkedData TimeMarkedData;

struct TimeMarkedData
{
	long timeInterval;
	int dataValue;
};

void TimeMarkedData_Init(TimeMarkedData* const me);
void TimeMarkedData_Cleanup(TimeMarkedData* const me);
void TimeMarkedData__setItsTMDQueue(TimeMarkedData* const me, struct TMDQueue* p_TMDQueue);