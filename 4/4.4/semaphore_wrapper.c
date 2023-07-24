#include <stdio.h>
#include <fcntl.h>
#include "semaphore_wrapper.h"


sem_t* semGet(int proj_id) {
    char path[32] = "/EltexSem.";
    sprintf(&(path[10]), "%d", proj_id);
    return sem_open(path, O_CREAT, 0666, 1);
}

void semLock(sem_t *sem) {
    sem_wait(sem);
}

void semUnlock(sem_t *sem) {
    sem_post(sem);
}

int semValue(sem_t *sem) {
    int value;
    sem_getvalue(sem, &value);
    return value;
}

void semDestroy(sem_t *sem) {
    sem_close(sem);
}