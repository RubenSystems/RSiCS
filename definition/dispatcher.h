//
//  dispatcher.h
//  RSiCS
//
//  Created by Ruben Ticehurst-James on 22/10/2022.
//

#ifndef dispatcher_h
#define dispatcher_h

#include <stdio.h>
#include <pthread.h>


#include "../config.h"


typedef void * (*dispatcher_task)(void *);

struct QueueNode {
	dispatcher_task task;
	void * arg;
	struct QueueNode * next;
	
};


struct DispatchQueue {
	struct QueueNode * begin;
	struct QueueNode * end;
	char running; // shutdown the queue
	pthread_mutex_t mutex;
	pthread_cond_t add_contition; // condition for waiting on add
	pthread_t threads [DISPATCHER_TASK_SIZE];
};



struct DispatchQueue init_dispatch_queue(void);

/*
 
 Run this task asyncrounously and allow the dispatcher
 to manage execution.
 
 */
void async_task(struct DispatchQueue *, dispatcher_task, void *);

/*
 If this is not called, items will be enqueued, but not dequueed. 
 */
void start_execution(struct DispatchQueue *);

/*
 Should be called like free() except this does not free anything it just tells
 the system to wait untill all tasks have been completed ;
 */
void join(struct DispatchQueue *);


/*
 Should be called only by dispatch queue.
 */
enum DequeueTaskStatus {
	DEQUEUE_NOITEM,
	DEQUEUE_EXECUTED
};

enum DequeueTaskStatus _dequeue_task(struct DispatchQueue *);




#endif /* dispatcher_h */
