#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "semaphore_wrapper.h"

#define FIFO_PATH "/tmp/fifo.2.10.tmp"

int main() {
    int semid = semGet(CUR_PROJ);
    semLock(semid);
    int fifoFD = open(FIFO_PATH, O_RDONLY);
    if (fifoFD == -1) {
        fprintf(stderr, "Unable to open FIFO\n");
        return 1;
    }
    long amount;
    read(fifoFD, &amount, sizeof(long));
    semUnlock(semid);
    close(fifoFD);
    for (long i = 0; i < amount; i++) {
        int rx;
        semLock(semid);
        fifoFD = open(FIFO_PATH, O_RDONLY);
        read(fifoFD, &rx, sizeof(int));
        close(fifoFD);
        semUnlock(semid);
        printf("%d ", rx);
    }
    printf("\n");
    return 0;
}