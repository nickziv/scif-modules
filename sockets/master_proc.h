#ifndef __MASTER_PROC_H
#define __MASTER_PROC_H

#include "mtc_queue.h"

struct mproc_state {
	struct queue *incoming;
	struct queue *results;
	pthread_t *worker_threads;
	int *kill_master;
	int workers;
};

struct task *execute_task(struct task *task);
void *master_process(void *params);

#endif /*__MASTER_PROC_H */
