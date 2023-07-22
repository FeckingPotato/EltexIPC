#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Wrong amount of arguments\n");
        return 1;
    }
    int pipeFD[2];
    if (pipe(pipeFD) == -1) {
        printf("Unable to create a pipe\n");
        return 1;
    }
    long amount = strtol(argv[1], NULL, 10);
    srand(time(NULL));
    switch (fork()) {
        case -1:
            printf("Unable to fork\n");
            return 1;
        case 0:
            close(pipeFD[0]);
            for (long i = 0; i < amount; i++) {
                int tx = rand() % 2000 - 1000;
                write(pipeFD[1], &tx, sizeof(int));
            }
            close(pipeFD[1]);
            return 0;
        default:
            close(pipeFD[1]);
            FILE* output = fopen("output.txt", "w");
            for (long i = 0; i < amount; i++) {
                int rx;
                read(pipeFD[0], &rx, sizeof(int));
                printf("%d ", rx);
                fprintf(output, "%d ", rx);
            }
            close(pipeFD[0]);
            fclose(output);
            printf("\n");
            return 0;
    }
}