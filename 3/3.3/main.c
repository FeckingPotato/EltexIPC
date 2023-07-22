#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int counter = 0;

void ignoreSigint(int sig) {
    counter++;
    if (counter < 3) {
        printf("I've just ignored SIGINT!\n");
        return;
    }
    printf("Exiting.\n");
    exit(sig);
}

int main() {
    signal(SIGINT, ignoreSigint);
    printf("PID: %d\n", getpid());
    FILE* file;
    file = fopen("log.txt", "w");
    unsigned int counter = 0;
    while (1) {
        printf("%d\n", counter);
        fprintf(file, "%d\n", counter);
        fflush(file);
        counter++;
        sleep(1);
    }
}