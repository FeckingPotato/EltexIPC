#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


#define FIFO_PATH "/tmp/fifo.2.10.tmp"

int main() {
    int fifoFD = open(FIFO_PATH, O_RDONLY);
    if (fifoFD == -1) {
        fprintf(stderr, "Unable to open FIFO\n");
        return 1;
    }
    long amount;
    read(fifoFD, &amount, sizeof(long));
    for (long i = 0; i < amount; i++) {
        int rx;
        read(fifoFD, &rx, sizeof(int));
        printf("%d ", rx);
    }
    printf("\n");
    close(fifoFD);
}