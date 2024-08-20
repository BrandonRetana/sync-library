// src/mutex/mutex.h
#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

typedef struct {
    pthread_cond_t cond;
    pthread_mutex_t internal_mutex;
    int locked; 
} mutex_t;

void mutex_init(mutex_t *mutex);
void mutex_lock(mutex_t *mutex);
void mutex_unlock(mutex_t *mutex);
void mutex_destroy(mutex_t *mutex);

#endif // MUTEX_H