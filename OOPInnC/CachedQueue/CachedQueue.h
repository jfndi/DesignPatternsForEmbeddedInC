#pragma once
#include "queue.h"

typedef struct CachedQueue CachedQueue;
struct CachedQueue {
	/*
	 * Base class. 
	 */
	Queue* queue;

	/*
	 * New attributes. 
	 */
	char filename[80];
	int numberOfElementsOnDisk;

	/*
	 * Aggregation in subclass. 
	 */
	Queue* outputQueue;

	/*
	 * Inherited virtual functions. 
	 */
	int (*isFull)(CachedQueue* const me);
	int (*isEmpty)(CachedQueue* const me);
	int (*getSize)(CachedQueue* const me);
	void (*insert)(CachedQueue* const me, int k);
	int (*remove)(CachedQueue* const me);

	/*
	 * New virtual functions. 
	 */
	void (*flush)(CachedQueue* const me);
	void (*load)(CachedQueue* const me);
};

/*
 * Constructor and destructor. 
 */
void CachedQueue_Init(
	CachedQueue* me,
	char* Name,
	int (*isFullfunction)(CachedQueue* const me),
	int (*isEmptyfunction)(CachedQueue* const me),
	int (*getSizefunction)(CachedQueue* const me),
	void (*insertfunction)(CachedQueue* const me, int k),
	int (*removefunction)(CachedQueue* const me),
	void (*flushfunction)(CachedQueue* const me),
	void (*load)(CachedQueue* const me)
);

void CachedQueue_Cleanup(CachedQueue* me);

/*
 * Operations. 
 */
int CachedQueue_isFull(CachedQueue* const me);
int CachedQueue_isEmpty(CachedQueue* const me);
int CachedQueue_getSize(CachedQueue* const me);
void CachedQueue_insert(CachedQueue* const me, int k);
int CachedQueue_remove(CachedQueue* const me);
void CachedQueue_flush(CachedQueue* const me);
void CachedQueue_load(CachedQueue* const me);