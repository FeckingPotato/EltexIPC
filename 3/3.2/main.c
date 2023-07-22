#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void ignoreSigint(int sig) {
    printf("I've just ignored SIGINT!\n");
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