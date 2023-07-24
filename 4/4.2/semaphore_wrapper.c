#include <sys/sem.h>
#include "semaphore_wrapper.h"

int semGet(int proj_id) {
    return semget(ftok("/etc/fstab", proj_id), 1, IPC_CREAT);
}

void semLock(int semid) {
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = -1;
    buf.sem_flg = 0;
    semop(semid, &buf, 1);
}

void semUnlock(int semid) {
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = 0;
    semop(semid, &buf, 1);
}

void semDestroy(int semid) {
    semctl(semid, 0, IPC_RMID);
}