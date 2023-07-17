#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    pid_t pid;
    switch(pid = fork()) {
        case -1:
	    perror("fork");
	    exit(EXIT_FAILURE);
        case 0:
	    for (int i = 1; i < argc/2+1; i++) {
	        long curNum = strtol(argv[i], NULL, 10);
	        printf("%d ", curNum*curNum);
	    }
	    printf("\n");
	    exit(EXIT_SUCCESS);
	default:
	    for (int i = argc/2+1; i < argc; i++) {
		long curNum = strtol(argv[i], NULL, 10);
		printf("%d ", curNum*curNum);
	    }
	    printf("\n");
	    exit(EXIT_SUCCESS);
    }
}
