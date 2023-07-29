#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "posixPort.h"
#include "msgStruct.h"

int done = 0;

void exitFunc(int) {
    done = 1;
    exit(0);
}

int main() {
    signal(SIGINT, exitFunc);
    int msqID = msgget(IPC_PRIVATE, IPC_CREAT);
    struct msgbuf rx, tx;
    tx.mtype = MSG_CONNECT;
    if (msgsnd(msqID, &tx, SIZE_MSG, 0) == -1) {
        perror(NULL);
        fprintf(stderr, "Unable to access the queue\n");
        return 1;
    }
    printf("Connected\n");
    while (!done) {
        msgrcv(msqID, &rx, SIZE_MSG, 0, 0);
        if (rx.mtype == MSG_EXIT) {
            printf("Server disconnected\n");
            exitFunc(0);
        }
        printf("%s\n", rx.text);
    }
	return 0;
}