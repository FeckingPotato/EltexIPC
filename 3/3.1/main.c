#include <stdio.h>
#include <unistd.h>

int main() {
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