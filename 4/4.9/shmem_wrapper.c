#include <fcntl.h>
#include <sys/mman.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include "shmem_wrapper.h"

static unsigned int memSize;

int shmGet(int proj_id, unsigned int size) {
    char name[32] = "/EltexShm.";
    sprintf(&(name[10]), "%d", proj_id);
    int fd = shm_open(name, O_CREAT | O_TRUNC |O_RDWR, 0666);
    ftruncate(fd, size);
    memSize = size;
    return fd;
}

void *shmAttach(int shmfd) {
    return mmap(NULL, memSize, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
}

void shmDetach(void *shm) {
    munmap(shm, memSize);
}

void shmRemove(int shmfd) {
    char path[32] = "/proc/self/fd/";
    sprintf(&(path[14]), "%d", shmfd);
    close(shmfd);
    shm_unlink(path);
}