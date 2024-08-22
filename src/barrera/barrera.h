#ifndef BARRIER_H
#define BARRIER_H

#include <pthread.h>

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;
    int total;
} barrier;

void barrier_init(barrier *barrier, int total);
void barrier_wait(barrier *barrier);
void barrier_destroy(barrier *barrier);

#endif
