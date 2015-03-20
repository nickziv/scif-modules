#ifndef __MTC_QUEUE_H
#define __MTC_QUEUE_H

#include <pthread.h>

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
};

struct queue *create_queue(int size);
void dispose_queue(struct queue *q);
void enqueue(struct task_desc *task, struct queue *q);
struct task_desc *front(struct queue *q);
void dequeue(struct queue *q);
struct task_desc *try_front_dequeue(struct queue *q);


#endif /* __MTC_QUEUE_H */

/*
 * NOTES:
 * [Code Optimization & Readability] Change **tasks to zero-length array
 */
