#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main() {
    printf("PID: %d\n", getpid());
    FILE* file = fopen("log.txt", "w");
    fclose(file);
    unsigned int counter = 0;
    while (1) {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        file = fopen("log.txt", "a");
        printf("%d\n", counter);
        fprintf(file, "%d\n", counter);
        fflush(file);
        counter++;
        fclose(file);
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        sleep(1);
    }
}