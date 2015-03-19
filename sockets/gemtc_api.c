#include <stdio.h>
#include "gemtc_api.h"
#include "mtc_queue.h"

void gemtc_setup(int queue_size, int workers)
{
	printf("gemtc_setup: Queue Size = %d, Workers = %d\n", queue_size, workers);

	/* initialize locks */
	pthread_mutex_init(&enqueue_lock, NULL);
	pthread_mutex_init(&dequeue_lock, NULL);
	pthread_mutex_init(&memcpy_lock, NULL);

	/* create queue */
	struct queue *q = create_queue(queue_size);
	/* delete queue */
	dispose_queue(q);

	return;
}

void gemtc_cleanup()
{
	printf("gemtc_cleanup\n");

	/* cleanup locks */
	pthread_mutex_destroy(&enqueue_lock);
	pthread_mutex_destroy(&dequeue_lock);
	pthread_mutex_destroy(&memcpy_lock);

	return;
}

void gemtc_push(int type, int threads, int id, void *params)
{
	printf("gemtc_push: Type = %d, Threads = %d, ID = %d, Params %s\n",
					type, threads, id, (params) ? "Exist" : "is NULL" );
	return;
}
void gemtc_poll(int *id, void **params)
{
	printf("gemtc_poll: ID = %d, Params %s\n",
					*id, (params) ? "Exist" : "is NULL" );
	return;
}
