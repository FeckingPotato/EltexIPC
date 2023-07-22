#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <wait.h>

int semaphore = 0;

void semInc(int sig) {
    semaphore++;
}

void semDec(int sig) {
    semaphore--;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Wrong amount of arguments\n");
        return 1;
    }
    long amount = strtol(argv[1], NULL, 10);
    srand(time(NULL));
    FILE* output;
    output = fopen("output.txt", "w");
    fclose(output);
    signal(SIGUSR1, semInc);
    signal(SIGUSR2, semDec);
    pid_t pid;
    switch (pid = fork()) {
        case -1:
            printf("Unable to fork\n");
            return 1;
        case 0: {
            while (semaphore != 0);
            output = fopen("output.txt", "r");
            fseek(output, 0, SEEK_END);
            long size = ftell(output);
            fseek(output, 0, SEEK_SET);
            char buffer[size+1];
            fread(buffer, 1, size, output);
            fclose(output);
            buffer[size] = '\0';
            printf("%s\n", buffer);
            return 0;
        }
        default:
            kill(pid, SIGUSR1);
            output = fopen("output.txt", "a");
            for (long i = 0; i < amount; i++) {
                int random = rand() % 2000 - 1000;
                fprintf(output, "%d ", random);
                fflush(output);
            }
            fclose(output);
            kill(pid, SIGUSR2);
            wait(NULL);
            return 0;
    }
}