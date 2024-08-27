#include "read-write.h"

void rwlock_init(rwlock *rw) {
    pthread_mutex_init(&rw->lock, NULL);
    pthread_cond_init(&rw->readers_ok, NULL);
    pthread_cond_init(&rw->writers_ok, NULL);
    rw->active_readers = 0;
    rw->waiting_writers = 0;
    rw->active_writers = 0;
}

void rwlock_acquire_read(rwlock *rw) {
    pthread_mutex_lock(&rw->lock);
    while (rw->active_writers > 0 || rw->waiting_writers > 0) {
        pthread_cond_wait(&rw->readers_ok, &rw->lock);
    }
    rw->active_readers++;
    pthread_mutex_unlock(&rw->lock);
}

void rwlock_release_read(rwlock *rw) {
    pthread_mutex_lock(&rw->lock);
    rw->active_readers--;
    if (rw->active_readers == 0 && rw->waiting_writers > 0) {
        pthread_cond_signal(&rw->writers_ok);
    }
    pthread_mutex_unlock(&rw->lock);
}

void rwlock_acquire_write(rwlock *rw) {
    pthread_mutex_lock(&rw->lock);
    rw->waiting_writers++;
    while (rw->active_writers > 0 || rw->active_readers > 0) {
        pthread_cond_wait(&rw->writers_ok, &rw->lock);
    }
    rw->waiting_writers--;
    rw->active_writers = 1;
    pthread_mutex_unlock(&rw->lock);
}

void rwlock_release_write(rwlock *rw) {
    pthread_mutex_lock(&rw->lock);
    rw->active_writers = 0;
    if (rw->waiting_writers > 0) {
        pthread_cond_signal(&rw->writers_ok);
    } else {
        pthread_cond_broadcast(&rw->readers_ok);
    }
    pthread_mutex_unlock(&rw->lock);
}

void rwlock_destroy(rwlock *rw) {
    pthread_mutex_destroy(&rw->lock);
    pthread_cond_destroy(&rw->readers_ok);
    pthread_cond_destroy(&rw->writers_ok);
}
