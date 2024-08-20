#include<pthread.h>
#include <stdio.h>
#include<stdlib.h>
#include<mutex.c>

#define NUM_THREADS 5

mutex_t mutex;

void test(void *arg){
    long thread_id = (long)arg;
    printf("Hilo %ld intentando adquirir el mutex...\n", thread_id);
    my_mutex_lock(&mutex);

    // Sección crítica
    printf("Hilo %ld en la sección crítica.\n", thread_id);
    sleep(1);  // Simula trabajo en la sección crítica

    printf("Hilo %ld liberando el mutex.\n", thread_id);
    my_mutex_unlock(&mutex);

    return NULL;    
}

int main() {
    pthread_t threads[NUM_THREADS];

    my_mutex_init(&mutex);

    // Crear hilos
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, test, (void*)i);
    }

    // Esperar a que los hilos terminen
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    my_mutex_destroy(&mutex);

    return 0;
}