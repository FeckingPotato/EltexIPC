#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Wrong amount of arguments\n");
        return 1;
    }
    int pipeFD1[2];
    int pipeFD2[2];
    if (pipe(pipeFD1) == -1 || pipe(pipeFD2) == -1) {
        printf("Unable to create pipes\n");
        return 1;
    }
    long amount = strtol(argv[1], NULL, 10);
    srand(time(NULL));
    FILE* output = fopen("output.txt", "w");
    switch (fork()) {
        case -1:
            printf("Unable to fork\n");
            return 1;
        case 0:
            close(pipeFD1[0]);
            close(pipeFD2[1]);
            for (long i = 0; i < amount; i++) {
                int tx = rand() % 2000 - 1000;
                write(pipeFD1[1], &tx, sizeof(int));
                int rx;
                read(pipeFD2[0], &rx, sizeof(int));
                printf("C: %d ", rx);
                fflush(stdout);
                fprintf(output, "C: %d ", rx);
                fflush(output);
            }
            close(pipeFD1[1]);
            close(pipeFD2[0]);
            return 0;
        default:
            close(pipeFD1[1]);
            close(pipeFD2[0]);
            for (long i = 0; i < amount; i++) {
                int rx;
                read(pipeFD1[0], &rx, sizeof(int));
                printf("P: %d ", rx);
                fprintf(output, "P: %d ", rx);
                int tx = rx * 2;
                write(pipeFD2[1], &tx, sizeof(int));
            }
            close(pipeFD1[0]);
            close(pipeFD2[1]);
            fclose(output);
            printf("\n");
            return 0;
    }
}