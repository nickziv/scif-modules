#ifndef __GEMTC_API_H
#define __GEMTC_API_H

#include <pthread.h>

pthread_mutex_t enqueue_lock;
pthread_mutex_t dequeue_lock;
pthread_mutex_t memcpy_lock;

void gemtc_setup(int queue_size, int workers);
void gemtc_cleanup();

void gemtc_push(int type, int threads, int id, void *params);
void gemtc_poll(int *id, void **params);

void gemtc_memcpy_host2dev();
void gemtc_memcpy_dev2host();

/* Possibly Unneeded */
void gemtc_malloc();
/* Possibly Unneeded */
void gemtc_free();


#endif
