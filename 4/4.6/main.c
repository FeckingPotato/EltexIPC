#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wait.h>
#include "semaphore_wrapper.h"

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
    sem_t* sem = semGet(CUR_PROJ);
    if (semValue(sem) == 0) {
        semUnlock(sem);
    }
    switch (fork()) {
        case -1:
            printf("Unable to fork\n");
            semDestroy(sem);
            return 1;
        case 0: {
            if (fork() == -1 || fork() == -1 || fork() == -1 || fork() == -1) {
                printf("Unable to fork\n");
                return 1;
            }
            semLock(sem);
            output = fopen("output.txt", "r");
            fseek(output, 0, SEEK_END);
            long size = ftell(output);
            fseek(output, 0, SEEK_SET);
            char buffer[size+1];
            fread(buffer, 1, size, output);
            fclose(output);
            semUnlock(sem);
            buffer[size] = '\0';
            printf("%s\n", buffer);
            return 0;
        }
        default:
            semLock(sem);
            output = fopen("output.txt", "a");
            for (long i = 0; i < amount; i++) {
                int random = rand() % 2000 - 1000;
                fprintf(output, "%d ", random);
                fflush(output);
            }
            fclose(output);
            semUnlock(sem);
            wait(NULL);
            semDestroy(sem);
            return 0;
    }
}