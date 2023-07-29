#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "posixPort.h"
#include "msgStruct.h"

int done = 0;

int msqID = -1;

void exitFunc(int) {
    done = 1;
    char path[32];
    sprintf(path, "/MQueue%d", IPC_PRIVATE);
    mq_unlink(path);
    mq_close(msqID);
    struct msgbuf tx;
    tx.mtype = MSG_EXIT;
    msgsnd(msqID, &tx, SIZE_MSG, 0);
    exit(0);
}

int main() {
    signal(SIGINT, exitFunc);
    msqID = msgget(IPC_PRIVATE, IPC_CREAT);
    printf("msqID: %d\n", msqID);
    printf("Waiting for client\n");
    struct msgbuf rx, tx;
    if (msgrcv(msqID, &rx, SIZE_MSG, MSG_CONNECT, 0) == -1) {
        perror("Unable to read the queue");
        exitFunc(0);
    }
    printf("Client connected\n");
    tx.mtype = MSG_DATA;
    FILE* urandom;
    while (!done) {
        urandom = fopen("/dev/urandom", "r");
        fread(tx.text, 1, SIZE_MSG, urandom);
        fclose(urandom);
        msgsnd(msqID, &tx, SIZE_MSG, 0);
        sleep(1);
    }
	return 0;
}
