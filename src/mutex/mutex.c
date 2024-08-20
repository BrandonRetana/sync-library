#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct{
    pthread_cond_t cond;
    pthread_mutex_t internal_mutex;
    int locked;
} mutex;


void mutex_init(mutex *m){
    pthread_cond_init(&m->cond, NULL);
    pthread_mutex_init(&m->internal_mutex, NULL);
    m->locked = 0;
}

void mutex_lock(mutex *m){
    pthread_mutex_lock(&m->internal_mutex);
    while (m->locked){
        pthread_cond_wait(&m->cond, &m->internal_mutex);
    }
    m->locked = 1;
    pthread_mutex_unlock(&m->internal_mutex);
}

void mutex_unlock(mutex *m){
    pthread_mutex_lock(&m->internal_mutex);
    m->locked = 0;
    pthread_cond_signal(&m->cond);
    pthread_mutex_unlock(&m->internal_mutex);   
}

void mutex_destroy(mutex *m){
    pthread_cond_destroy(&m->cond);
    pthread_mutex_destroy(&m->internal_mutex);
}