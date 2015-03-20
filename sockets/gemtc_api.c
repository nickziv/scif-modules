#include <stdio.h>
#include <stdlib.h>
#include "gemtc_api.h"
#include "mtc_queue.h"

struct queue *incoming_work, *completed_result;

void gemtc_setup(int queue_size, int workers)
{
	printf("gemtc_setup: Queue Size = %d, Workers = %d\n", queue_size, workers);

	/* initialize locks */
	pthread_mutex_init(&enqueue_lock, NULL);
	pthread_mutex_init(&dequeue_lock, NULL);
	pthread_mutex_init(&memcpy_lock, NULL);

	/* allocate queues */
	incoming_work = create_queue(queue_size);
	completed_result = create_queue(queue_size);
}

void gemtc_cleanup()
{
	printf("gemtc_cleanup\n");

	/* cleanup locks */
	pthread_mutex_destroy(&enqueue_lock);
	pthread_mutex_destroy(&dequeue_lock);
	pthread_mutex_destroy(&memcpy_lock);

	/* cleanup queues */
	dispose_queue(incoming_work);
	dispose_queue(completed_result);
}

void gemtc_push(int type, int threads, int id, void *params)
{
	printf("gemtc_push: Type = %d, Threads = %d, ID = %d, Params %s\n",
					type, threads, id, (params) ? "Exist" : "is NULL" );

	struct task_desc *task = (struct task_desc *) malloc(sizeof(struct task_desc));	
	task->task_id = id;
	task->task_type = type;
	task->num_threads = threads;
	task->params = params;

	pthread_mutex_lock(&enqueue_lock);
	enqueue(task, incoming_work);
	pthread_mutex_unlock(&enqueue_lock);
}

void gemtc_poll(int *id, void **params)
{
	printf("gemtc_poll: ID = %d, Params %s\n",
					*id, (params) ? "Exist" : "is NULL" );

	struct task_desc *task;

	/* try to dequeue from the front */
	pthread_mutex_lock(&dequeue_lock);
	task = try_front_dequeue(completed_result);
	pthread_mutex_unlock(&dequeue_lock);

	/* if nothing was returned set error values and return */
	if (!task) {
		*id = -1;
		*params = NULL;
		return;
	}
	
	/* else pass the pointers with the results */
	*id = task->task_id;
	*params = task->params;

	/* cleanup task */
	free(task);
}

void *gemtc_malloc(unsigned int nbytes)
{
	return malloc(nbytes);
}

void gemtc_free(void *loc) {
	return free(loc);
}

/* For the memcpy functions use Xeon Phi's API */
