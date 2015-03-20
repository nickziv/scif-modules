#ifndef __MTC_QUEUE_H
#define __MTC_QUEUE_H

#include <pthread.h>
#include <semaphore.h>

struct task_desc {
	int task_id;
	int task_type;
	int num_threads;
	void *params;
};

struct queue {
	struct task_desc **tasks;
	int capacity;
	int rear;
	int front;
	pthread_mutex_t lock;
	sem_t task_sem;
	sem_t spaces_sem;
};

struct queue *create_queue(int size);
void dispose_queue(struct queue *q);
void enqueue(struct task_desc *task, struct queue *q);
struct task_desc *dequeue(struct queue *q);


#endif /* __MTC_QUEUE_H */

/*
 * NOTES:
 * [Code Optimization & Readability] Change **tasks to zero-length array
 * [Reasoning] Look at the Finite Producer-Consumer Solution of LBoS
 */
