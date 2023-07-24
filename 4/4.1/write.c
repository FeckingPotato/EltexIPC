#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "semaphore_wrapper.h"

#define FIFO_PATH "/tmp/fifo.2.10.tmp"

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
    int semid = semGet(CUR_PROJ);
    semLock(semid);
    int fifoFD = open(FIFO_PATH, O_WRONLY);
    if (fifoFD == -1) {
        fprintf(stderr, "Unable to open FIFO\n");
        return 1;
    }
    write(fifoFD, &amount, sizeof(long));
    close(fifoFD);
    semUnlock(semid);
    srand(time(NULL));
    for (long i = 0; i < amount; i++) {
        int tx = rand() % 2000 - 1000;
        semLock(semid);
        fifoFD = open(FIFO_PATH, O_WRONLY);
        write(fifoFD, &tx, sizeof(int));
        close(fifoFD);
        semUnlock(semid);
    }
    unlink(FIFO_PATH);
    return 0;
}