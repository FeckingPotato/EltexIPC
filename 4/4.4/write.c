#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "semaphore_wrapper.h"

#define FIFO_PATH "/tmp/fifo.4.4.tmp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Wrong amount of arguments\n");
        return 1;
    }
    unlink(FIFO_PATH);
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        fprintf(stderr, "Unable to get FIFO\n");
        return 1;
    }
    long amount = strtol(argv[1], NULL, 10);
    sem_t* sem = semGet(CUR_PROJ);
    if (semValue(sem) == 0) {
        semUnlock(sem);
    }
    semLock(sem);
    int fifoFD = open(FIFO_PATH, O_WRONLY);
    if (fifoFD == -1) {
        fprintf(stderr, "Unable to open FIFO\n");
        return 1;
    }
    write(fifoFD, &amount, sizeof(long));
    close(fifoFD);
    semUnlock(sem);
    srand(time(NULL));
    for (long i = 0; i < amount; i++) {
        int tx = rand() % 2000 - 1000;
        semLock(sem);
        fifoFD = open(FIFO_PATH, O_WRONLY);
        write(fifoFD, &tx, sizeof(int));
        close(fifoFD);
        semUnlock(sem);
    }
    unlink(FIFO_PATH);
    return 0;
}