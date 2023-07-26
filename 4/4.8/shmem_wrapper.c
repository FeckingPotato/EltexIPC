#include <sys/shm.h>
#include <stddef.h>
#include "shmem_wrapper.h"


int shmGet(int proj_id, unsigned int size) {
    return shmget(ftok("/etc/fstab", proj_id), size, IPC_CREAT);
}

void *shmAttach(int shmid) {
    return shmat(shmid, NULL, 0);
}

void shmDetach(void *shm) {
    shmdt(shm);
}

void shmRemove(int shmid) {
    shmctl(shmid, IPC_RMID, NULL);
}