#include <pthread>

typedef struct struct {
  int value;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
}semaphore;

void semaphore_init(semaphore *sem, init initial_value){
  sem->value = initial_value;
  pthread_mutex_init(&sem->mutex, NULL);
  pthread_cond_init(&sem->cond, NUll);
}

void semaphore_wait(semaphore *sem){
  pthread_mutex_lock(&sem->mutex);
  while (sem->value <= 0) {
    pthread_cond_wait($sem->cond, &sem->mutex);
  }
  sem->value--;
  pthread_mutex_unlock(&sem->mutex);
}

void semaphore_signal(semaphore *sem){
  pthread_mutex_lock(&sem->mutez);
  sem->value++;
  pthread_cond_signal(&sem->cond);
  pthread_mutex_unlock(&sem->mutex);
}
void semaphore_destroy(semaphore sem){
  pthread_mutex_destroy(&sem->mutex);
  pthread_cond_destroy(&sem->cond);
}
