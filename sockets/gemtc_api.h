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

void gemtc_memcpy_host2dev(void *host, void *device, int size);
void gemtc_memcpy_dev2host(void *device, void *host, int size);

void *gemtc_malloc(unsigned int nbytes);
void gemtc_free(void *loc);


#endif /* __GEMTC_API_H */
