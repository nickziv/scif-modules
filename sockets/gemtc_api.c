#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gemtc_api.h"
#include "mtc_queue.h"

#include <assert.h>

struct queue *incoming_work, *completed_result;

void gemtc_setup(int queue_size, int workers)
{
	printf("gemtc_setup: Queue Size = %d, Workers = %d\n", queue_size, workers);

	assert(queue_size > 0);

	/* allocate queues */
	incoming_work = create_queue(queue_size);
	completed_result = create_queue(queue_size);
}

void gemtc_cleanup()
{
	printf("gemtc_cleanup\n");

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

	enqueue(task, incoming_work);
}

void gemtc_poll(int *id, void **params)
{
	printf("gemtc_poll: ID = %d, Params %s\n",
					*id, (params) ? "Exist" : "is NULL" );

	struct task_desc *task;

	task = dequeue(completed_result);

	assert(task != NULL);
	
	/* pass the pointers with the results */
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
void gemtc_memcpy_host2dev(void *host, void *device, size_t size)
{
	assert(host != 0);
	assert(device != 0);

	memcpy(host, device, size);
}

void gemtc_memcpy_dev2host(void *device, void *host, size_t size)
{
	assert(device != 0);
	assert(host != 0);

	memcpy(device, host, size);
}
