#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <pthread.h>

typedef struct {
  int permits;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
} semaphore;

void semaphore_init(semaphore *sem, int initial_permits);
void semaphore_wait(semaphore *sem);
void semaphore_signal(semaphore *sem);
void semaphore_destroy(semaphore *sem);

#endif
