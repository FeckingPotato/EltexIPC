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
    int counter = 2;

    signal(SIGINT, exitFunc);
    int msqID = msgget(IPC_PRIVATE, IPC_CREAT);
    printf("msqID: %d\n", msqID);
    struct msgbuf rx, tx;
    tx.mtype = SERVER_ID;
    while (!done) {
        msgrcv(msqID, &rx, SIZE_MSG, SERVER_ID, 0);
        if (rx.txID == 0) {
            counter++;
            tx.mtype = HANDSHAKE_ID;
            *((int *) tx.text) = counter;
            msgsnd(msqID, &tx, SIZE_MSG, 0);
            printf("New client: %d\n", counter);
            continue;
        }
        printf("Message from %d: %s\n", rx.txID, rx.text);
        tx = rx;
        for (tx.mtype = 3; tx.mtype <= counter; tx.mtype++) {
            if (tx.mtype == tx.txID) {
                continue;
            }
            msgsnd(msqID, &tx, SIZE_MSG, 0);
        }
    }
    return 0;
}
