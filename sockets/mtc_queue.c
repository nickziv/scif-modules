#include "mtc_queue.h"
#include <stdlib.h>

struct queue *create_queue(int size)
{
	struct queue *q = (struct queue *) malloc(sizeof(struct queue));

	q->tasks = (struct task_desc **) malloc(sizeof(struct task_desc)*size);
	q->capacity = size;
	q->front = 1;
	q->rear = 0;
	pthread_mutex_init(&q->write_lock, NULL);

	return q;
}

void dispose_queue(struct queue *q)
{
	free(q->tasks);
	pthread_mutex_destroy(&q->write_lock);
	free(q);
}
