#include<pthread.h>
#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<../mutex/mutex.h>
#include <../semaforo/semaforo.h>
#include <../barrera/barrera.h>


#define NUM_THREADS 5

barrier barr;
int shared_counter = 0;

void *thread_func(void *arg) {
    int id = *(int*)arg;
    printf("Thread %d llegando a la primera barrera.\n", id);
    barrier_wait(&barr);
    printf("Thread %d pasando la primera barrera.\n", id);

    // Incremento del contador sin mutex
    shared_counter++;

    printf("Thread %d llegando a la segunda barrera.\n", id);
    barrier_wait(&barr);
    printf("Thread %d pasando la segunda barrera.\n", id);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    barrier_init(&barr, NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    barrier_destroy(&barr);

    printf("Valor final del contador compartido: %d\n", shared_counter);

    return 0;
}
