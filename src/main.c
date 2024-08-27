#include<pthread.h>
#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<../mutex/mutex.h>
#include <../semaforo/semaforo.h>
#include <../barrera/barrera.h>
#include <../read-write-lock/read-write.h>

#define NUM_READERS 5
#define NUM_WRITERS 2
#define NUM_READS 10
#define NUM_WRITES 5

rwlock rwlock_t;
int shared_data = 0;

void *reader_function(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < NUM_READS; i++) {
        rwlock_acquire_read(&rwlock_t);
        printf("Reader %d: Read shared_data as %d\n", id, shared_data);
        rwlock_release_read(&rwlock_t);
    }
    return NULL;
}

void *writer_function(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < NUM_WRITES; i++) {
        rwlock_acquire_write(&rwlock_t);
        shared_data++;
        printf("Writer %d: Incremented shared_data to %d\n", id, shared_data);
        rwlock_release_write(&rwlock_t);
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    rwlock_init(&rwlock_t);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i;
        pthread_create(&readers[i], NULL, reader_function, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i;
        pthread_create(&writers[i], NULL, writer_function, &writer_ids[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    rwlock_destroy(&rwlock_t);

    printf("Final shared_data value: %d\n", shared_data);

    return 0;
}

