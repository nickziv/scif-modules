#include "master_proc.h"

struct task_desc *execute_task(struct task_desc *task)
{
	switch (task->task_type) {
	case 0:
		/* STUB */
		break;
	case 1:
		/* STUB */
		break;
	default:
		/* Error not supported! */
		break;
	}
	
	return task;
}

void *worker_handler(void *data)
{
  struct mproc_state *mps = (struct mproc_state *) data;
	struct task_desc *task;

	while(!(*(mps->kill_master))) {
		task = dequeue(mps->incoming);
		task = execute_task(task);
		enqueue(task, mps->results);
	}

	return NULL;
}


/*
 * NOTES:
 * TODO: switch case numbers above should be in an enum
 */
