#include<pthread.h>
#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<../mutex/mutex.h>
#include <../semaforo/semaforo.h>

int main() {
    semaphore sem;
    semaphore_init(&sem, 1);

    printf("Probando el semáforo...\n");
    semaphore_wait(&sem);
    printf("Dentro de la sección crítica.\n");
    semaphore_signal(&sem);
    printf("Fuera de la sección crítica.\n");

    semaphore_destroy(&sem);
    return 0;
}
