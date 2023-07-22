#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void ignoreSigint(int sig) {
    printf("I've just ignored SIGINT!\n");
}

int main() {
    signal(SIGINT, ignoreSigint);
    printf("PID: %d\n", getpid());
    FILE* file = fopen("log.txt", "w");
    fclose(file);
    unsigned int counter = 0;
    while (1) {
        file = fopen("log.txt", "a");
        printf("%d\n", counter);
        fprintf(file, "%d\n", counter);
        fflush(file);
        counter++;
        fclose(file);
        sleep(1);
    }
}