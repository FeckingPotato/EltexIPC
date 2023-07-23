#include <stdio.h>
#include <signal.h>
#include <sys/msg.h>
#include "msgStruct.h"

int done = 0;

void exitFunc(int) {
    done = 1;
}

int main() {
    signal(SIGINT, exitFunc);
    int msqID;
    printf("Input the message queue ID: ");
    scanf("%d", &msqID);
    struct msgbuf rx, tx;
    tx.mtype = MSG_CONNECT;
    if (msgsnd(msqID, &tx, SIZE_MSG, 0) == -1) {
        fprintf(stderr, "Unable to access the queue\n");
        return 1;
    }
    printf("Connected\n");
    tx.mtype = MSG_CLIENT;
    stdin->_IO_read_ptr = stdin->_IO_read_end;
    while (!done) {
        printf("Your input: ");
        fgets(tx.text, SIZE_MSG, stdin);
        msgsnd(msqID, &tx, SIZE_MSG, 0);
        msgrcv(msqID, &rx, SIZE_MSG, 0, 0);
        if (rx.mtype == MSG_EXIT) {
            printf("Server disconnected\n");
            return 0;
        }
        printf("Server: %s", rx.text);
    }
    tx.mtype = MSG_EXIT;
    msgsnd(msqID, &tx, SIZE_MSG, 0);
    return 0;
}