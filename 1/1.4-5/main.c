#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int input;
    char arg1[64], arg2[64];
        printf("Pick a program to run:\n"
               "1. String concatenation\n"
               "2. Integer sum\n"
               "3. List processes\n");
        scanf("%d", &input);
        switch (input) {
            default:
                printf("Wrong option");
                exit(EXIT_FAILURE);
            case 1: 
                printf("Input first string: ");
                scanf("%s", arg1);
                printf("Input second string: ");
                scanf("%s", arg2);
                execl("./concat.out", arg1, arg2);
                exit(EXIT_SUCCESS);
            case 2:
                printf("Input first integer: ");
                scanf("%s", arg1);
                printf("Input second integer: ");
                scanf("%s", arg2);
                execl("./sum.out", arg1, arg2);
                exit(EXIT_SUCCESS);
            case 3:
                execlp("ps", "ps", "aux");
		exit(EXIT_SUCCESS);
        }
}
