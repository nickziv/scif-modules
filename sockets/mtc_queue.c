#include "mtc_queue.h"
#include <stdlib.h>

static int is_empty(struct queue *q)
{
	return (q->rear + 1) % q->capacity == q->front;
}

static int is_full(struct queue *q)
{
	return (q->rear + 2) % q->capacity == q->front;
}

struct queue *create_queue(int size)
{
	struct queue *q = (struct queue *) malloc(sizeof(struct queue));

	q->tasks = (struct task_desc **) malloc(sizeof(struct task_desc) * size);
	q->capacity = size;
	q->front = 1;
	q->rear = 0;

	return q;
}

void dispose_queue(struct queue *q)
{
	free(q->tasks);
	free(q);
}

void enqueue(struct task_desc *task, struct queue *q)
{
	/* Use Polling for now (may have to change in the future) */
	while (is_full(q)); /* I'm weary of this */


	/* WARNING: This will fail if mod capacity is less or equal to 0 */
	int index = (q->rear + 1) % (q->capacity);
	q->tasks[index] = task;
	q->rear = index;

}

struct task_desc *front(struct queue *q)
{
	/* Use Polling for now (may have to change in the future) */
	while (is_empty(q));

	struct task_desc *task = (struct task_desc *) malloc(sizeof(struct task_desc));
	*task = *(q->tasks[q->front]); /* WARNING: THAT MAY BE NOT WHAT I EXPECT! */

	return task; /* Again very weary of this */
}

void dequeue(struct queue *q)
{
	/* Use Polling for now (may have to change in the future) */
	while (is_empty(q));

	q->front = (q->front + 1) % (q->capacity);
}

struct task_desc *try_front_dequeue(struct queue *q)
{
	if (is_empty(q)) {
		return NULL;
	}

	struct task_desc *task = (struct task_desc *) malloc(sizeof(struct task_desc));
	*task = *(q->tasks[q->front]);
	q->front = (q->front + 1) % (q->capacity);

	return task;
}
