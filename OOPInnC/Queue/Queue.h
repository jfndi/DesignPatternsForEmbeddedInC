#pragma once
/**
 * Queue.h:
 * ========
 * 
 * Definition of a Queue in an OOP oriented fashion in C.
 * 
 */

#define QUEUE_SIZE	10

/*
 * class Queue. 
 */
typedef struct Queue Queue;
struct Queue {
	/*
	 * Attributes. 
	 */
	int buffer[QUEUE_SIZE];
	int head;
	int size;
	int tail;

	/*
	 * Methods. 
	 */
	int (*isFull)(Queue* const me);
	int (*isEmpty)(Queue* const me);
	int (*getSize)(Queue* const me);
	void (*insert)(Queue* const me, int k);
	int (*remove)(Queue* const me);
};

/*
 * Constructor and destructor. 
 */
void Queue_Init(
	Queue* const me,
	int (*isFullfunction)(Queue* const me),
	int (*isEmptyfunction)(Queue* const me),
	int (*getSizefunction)(Queue* const me),
	void (*insertfunction)(Queue* const me, int k),
	int (*removefunction)(Queue* const me)
);

void Queue_Cleanup(Queue* const me);

/*
 * Operations. 
 */
int Queue_isFull(Queue* const me);
int Queue_isEmpty(Queue* const me);
int Queue_getSize(Queue* const me);
void Queue_insert(Queue* const me, int k);
int Queue_remove(Queue* const me);

Queue* Queue_Create(void);
void Queue_Destroy(Queue* const me);