#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void ignore(int sig) {
    if (sig == SIGINT) {
        printf("I've just ignored SIGINT!\n");
    }
    else {
        printf("I've just ignored SIGQUIT!\n");
    }
}

int main() {
    signal(SIGINT, ignore);
    signal(SIGQUIT, ignore);
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