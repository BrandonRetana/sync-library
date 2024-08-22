#include "semaforo.h"

void semaphore_init(semaphore *sem, int initial_permits){
  sem->permits = initial_permits;
  pthread_mutex_init(&sem->mutex, NULL);
  pthread_cond_init(&sem->cond, NULL);
}

void semaphore_wait(semaphore *sem){
  pthread_mutex_lock(&sem->mutex);
  while (sem->permits <= 0) {
    pthread_cond_wait(&sem->cond, &sem->mutex);
  }
  sem->permits--;
  pthread_mutex_unlock(&sem->mutex);
}

void semaphore_signal(semaphore *sem){
  pthread_mutex_lock(&sem->mutex);
  sem->permits++;
  pthread_cond_signal(&sem->cond);
  pthread_mutex_unlock(&sem->mutex);
}

void semaphore_destroy(semaphore *sem){
  pthread_mutex_destroy(&sem->mutex);
  pthread_cond_destroy(&sem->cond);
}

