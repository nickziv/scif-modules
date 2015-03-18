#include <stdio.h>
#include "gemtc_api.h"

void gemtc_setup(int queue_size, int workers)
{
	printf("gemtc_setup: Queue Size = %d, Workers = %d\n", queue_size, workers);
	return;
}

void gemtc_cleanup()
{
	printf("gemtc_cleanup\n");
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

void gemtc_memcpy_host2dev() { /* STUB */ }

void gemtc_memcpy_dev2host() { /* STUB */ }
