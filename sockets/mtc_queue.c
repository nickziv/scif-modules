#include "mtc_queue.h"
#include <stdlib.h>

struct queue *create_queue(int size)
{
	struct queue *q = (struct queue *) malloc(sizeof(struct queue));

	q->tasks = (struct task_desc **) malloc(sizeof(struct task_desc) * size);
	q->capacity = size;
	q->front = 1;
	q->rear = 0;
	pthread_mutex_init(&q->lock, NULL);
	sem_init(&q->task_sem, 0, 0);
	sem_init(&q->spaces_sem, 0, size);

	return q;
}

void dispose_queue(struct queue *q)
{
	free(q->tasks);
	pthread_mutex_destroy(&q->lock);
	sem_destroy(&q->task_sem);
	sem_destroy(&q->spaces_sem);
	free(q);
}

void enqueue(struct task_desc *task, struct queue *q)
{
	sem_wait(&q->spaces_sem);
	pthread_mutex_lock(&q->lock);

		int index = (q->rear + 1) % (q->capacity);
		q->tasks[index] = task;
		q->rear = index;

	pthread_mutex_unlock(&q->lock);
	sem_post(&q->task_sem);
}

struct task_desc *dequeue(struct queue *q)
{
	sem_wait(&q->task_sem);
	pthread_mutex_lock(&q->lock);

		struct task_desc *task = (struct task_desc *) malloc(sizeof(struct task_desc));
		*task = *(q->tasks[q->front]); /* WARNING: THIS MAY NOT BE WHAT I ASSUME IT IS */
		q->front = (q->front + 1) % (q->capacity);

	pthread_mutex_unlock(&q->lock);
	sem_post(&q->spaces_sem);

	return task;
}
