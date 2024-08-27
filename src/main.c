#include<pthread.h>
#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <../semaforo/semaforo.h>
#include <../barrera/barrera.h>
#include <../read-write-lock/read-write.h>

#define NUM_THREADS 5

// Prueba de barrera
void *test_barrier(void *arg) {
    barrier *bar = (barrier *)arg;
    printf("Hilo %ld esperando en la barrera\n", pthread_self());
    barrier_wait(bar);
    printf("Hilo %ld ha cruzado la barrera\n", pthread_self());
    return NULL;
}

// Prueba de semáforo
void *test_semaphore(void *arg) {
    semaphore *sem = (semaphore *)arg;
    semaphore_wait(sem);
    printf("Hilo %ld ha pasado el semáforo\n", pthread_self());
    sleep(1); // ejemplo de alguna tarea
    printf("Hilo %ld va a liberar el semáforo\n", pthread_self());
    semaphore_signal(sem);
    return NULL;
}


// Prueba de read-write lock
void *test_rwlock_read(void *arg) {
    rwlock *rw = (rwlock *)arg;
    rwlock_acquire_read(rw);
    printf("Hilo %ld leyendo\n", pthread_self());
    sleep(1); // Simular tarea de lectura
    printf("Hilo %ld terminó de leer\n", pthread_self());
    rwlock_release_read(rw);
    return NULL;
}

void *test_rwlock_write(void *arg) {
    rwlock *rw = (rwlock *)arg;
    rwlock_acquire_write(rw);
    printf("Hilo %ld escribiendo\n", pthread_self());
    sleep(2); // Simular tarea de escritura
    printf("Hilo %ld terminó de escribir\n", pthread_self());
    rwlock_release_write(rw);
    return NULL;
}


int main() {

    pthread_t threads[NUM_THREADS];

    // Prueba de barrera
    printf("PRUEBA DE LA BARRERA\n");
    barrier bar;
    barrier_init(&bar, NUM_THREADS);
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, test_barrier, &bar);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    barrier_destroy(&bar);


    // Prueba de semáforo
    printf("\nPRUEBA DEL SEMÁFORO\n");
    semaphore sem;
    semaphore_init(&sem, 3); // Permitir que 3 hilos entren simultáneamente
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, test_semaphore, &sem);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    semaphore_destroy(&sem);

    // Prueba de read-write lock
    printf("\nPRUEBA DEL READ-WRITE LOCK\n");
    rwlock rw;
    rwlock_init(&rw);
    for (int i = 0; i < NUM_THREADS; i++) {
        if (i % 2 == 0) {
            pthread_create(&threads[i], NULL, test_rwlock_read, &rw);
        } else {
            pthread_create(&threads[i], NULL, test_rwlock_write, &rw);
        }
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    rwlock_destroy(&rw);

    return 0;
}