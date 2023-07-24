#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "semaphore_wrapper.h"

#define FIFO_PATH "/tmp/fifo.4.4.tmp"

int main() {
    sem_t* sem = semGet(CUR_PROJ);
    semLock(sem);
    int fifoFD = open(FIFO_PATH, O_RDONLY);
    if (fifoFD == -1) {
        fprintf(stderr, "Unable to open FIFO\n");
        semDestroy(sem);
        return 1;
    }
    long amount;
    read(fifoFD, &amount, sizeof(long));
    semUnlock(sem);
    close(fifoFD);
    for (long i = 0; i < amount; i++) {
        int rx;
        semLock(sem);
        fifoFD = open(FIFO_PATH, O_RDONLY);
        read(fifoFD, &rx, sizeof(int));
        close(fifoFD);
        semUnlock(sem);
        printf("%d ", rx);
    }
    printf("\n");
    semDestroy(sem);
    return 0;
}