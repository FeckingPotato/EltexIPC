#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void finished_parent() {
    printf("Parent finished\n");
}

void finished_child() {
    printf("Child finished\n");
}

int main(int argc, char* argv[]) {
    pid_t pid;
    switch(pid = fork()) {
        case -1:
	    perror("fork");
	    exit(EXIT_FAILURE);
        case 0:
	    printf("Child arguments: ");
	    for (int i = 0; i < argc; i++) {
	        printf("%s ", argv[i]);
	    }
	    printf("\n");
            atexit(finished_child);
	    exit(EXIT_SUCCESS);
	default:
	    printf("Parent arguments: ");
	    for (int i = 0; i < argc; i++) {
		printf("%s ", argv[i]);
	    }
	    printf("\n");
	    atexit(finished_parent);
	    exit(EXIT_SUCCESS);
    }
}
