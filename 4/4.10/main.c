#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <wait.h>
#include "shmem_wrapper.h"

#define AMOUNT 10
#define FLAG_PARENT 0
#define FLAG_CHILD 4
#define FLAG_AVGREADY 1
#define FLAG_EXIT 255
int *flag;

void sigHandler(int) {
    *flag = FLAG_EXIT;
}

int main() {
    signal(SIGINT, sigHandler);
    int shmfd  = shmGet(CUR_PROJ, (AMOUNT + 6) * sizeof(int));
    void *shmem = shmAttach(shmfd);
    flag = (int *) shmem; // size == 1
    int *numbers = (&((int *) shmem)[2]); // size == AMOUNT
    int *min = (&((int *) shmem)[AMOUNT]); // size == 1
    int *max = (&((int *) shmem)[AMOUNT+1]); // size == 1
    int *counter = (&((int *) shmem)[AMOUNT+2]); // size == 1
    int *sum = (&((int *) shmem)[AMOUNT+3]); // size == 1
    int *avg = (&((int *) shmem)[AMOUNT+4]); // size == 1
    *flag = FLAG_PARENT;
    *counter = 0;
    while (*flag != FLAG_EXIT) {
        pid_t childPid;
        switch (childPid = fork()) {
            case -1:
                fprintf(stderr, "Unable to fork\n");
                shmDetach(shmem);
                shmRemove(shmfd);
                return 1;
            case 0: {
                while (*flag != FLAG_CHILD);
                *min = numbers[0];
                *max = numbers[0];
                printf("Generated numbers: %d ", numbers[0]);
                for (unsigned int i = 1; i < AMOUNT; i++) {
                    printf("%d ", numbers[i]);
                }
                printf("\n");
                switch (fork()) {
                    case -1:
                        fprintf(stderr, "Unable to fork\n");
                        shmDetach(shmem);
                        shmRemove(shmfd);
                        return 1;
                    case 0:
                        for (unsigned int i = 1; i < AMOUNT; i++) {
                            if (numbers[i] > *max) {
                                *max = numbers[i];
                            }
                        }
                        (*flag)--;
                        return 0;
                    default:
                        switch (fork()) {
                            case -1:
                                fprintf(stderr, "Unable to fork\n");
                                shmDetach(shmem);
                                shmRemove(shmfd);
                                return 1;
                            case 0:
                                for (unsigned int i = 1; i < AMOUNT; i++) {
                                    if (numbers[i] < *min) {
                                        *min = numbers[i];
                                    }
                                }
                                (*flag)--;
                                return 0;
                            default:
                                switch (fork()) {
                                    case -1:
                                        fprintf(stderr, "Unable to fork\n");
                                        shmDetach(shmem);
                                        shmRemove(shmfd);
                                        return 1;
                                    case 0:
                                        *sum = 0;
                                        for (unsigned int i = 1; i < AMOUNT; i++) {
                                            *sum += numbers[i];
                                        }
                                        (*flag)--;
                                        return 0;
                                    default:
                                        while (*flag != FLAG_AVGREADY);
                                        *avg = *sum / AMOUNT;
                                        *flag = FLAG_PARENT;
                                        return 0;
                                }
                        }
                }

            }
            default:
                srand(time(NULL));
                while (*flag != FLAG_PARENT);
                for (unsigned int i = 0; i < AMOUNT; i++) {
                    numbers[i] = rand() % 2000 - 1000;
                }
                *flag = FLAG_CHILD;
                while (*flag != FLAG_PARENT);
                printf("Min: %d\n"
                       "Max: %d\n"
                       "Sum: %d\n"
                       "Avg: %d\n", *min, *max, *sum, *avg);
                (*counter)++;
                sleep(1);
                waitpid(childPid, NULL, 0);
        }
    }
    printf("Program executed %d times\n", *counter);
    shmDetach(shmem);
    shmRemove(shmfd);
    return 0;
}
