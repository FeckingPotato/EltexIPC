#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msgStruct.h"

int done = 0;

void exitFunc(int) {
    done = 1;
}

int main() {
    signal(SIGINT, exitFunc);
    int msqID = msgget(IPC_PRIVATE, IPC_CREAT);
    printf("msqID: %d\n", msqID);
    printf("Waiting for client\n");
    struct msgbuf rx, tx;
    msgrcv(msqID, &rx, SIZE_MSG, MSG_CONNECT, 0);
    printf("Client connected\n");
    tx.mtype = MSG_SERVER;
    stdin->_IO_read_ptr = stdin->_IO_read_end;
    while (!done) {
        msgrcv(msqID, &rx, SIZE_MSG, 0, 0);
        if (rx.mtype == MSG_EXIT) {
            printf("Client disconnected\n");
            return 0;
        }
        printf("Client: %s"
               "Your input: ", rx.text);
        fgets(tx.text, SIZE_MSG, stdin);
        msgsnd(msqID, &tx, SIZE_MSG, 0);
    }
    tx.mtype = MSG_EXIT;
    msgsnd(msqID, &tx, SIZE_MSG, 0);
    return 0;
}
