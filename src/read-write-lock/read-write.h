#ifndef RWLOCK_H
#define RWLOCK_H

#include <pthread.h>

typedef struct {
    pthread_mutex_t lock;
    pthread_cond_t readers_ok;
    pthread_cond_t writers_ok;
    int active_readers;
    int waiting_writers;
    int active_writers;
} rwlock;

void rwlock_init(rwlock *rw);
void rwlock_acquire_read(rwlock *rw);
void rwlock_release_read(rwlock *rw);
void rwlock_acquire_write(rwlock *rw);
void rwlock_release_write(rwlock *rw);
void rwlock_destroy(rwlock *rw);

#endif
