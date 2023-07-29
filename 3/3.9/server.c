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
    long counter = 2;

    signal(SIGINT, exitFunc);
    int msqID = msgget(IPC_PRIVATE, IPC_CREAT);
    printf("msqID: %d\n", msqID);
    struct msgbuf rx, tx;
    while (!done) {
        msgrcv(msqID, &rx, SIZE_MSG, SERVER_ID, 0);
        long txID = *((long *) rx.mtext);
        if (txID == 0) {
            counter++;
            tx.mtype = HANDSHAKE_ID;
            *((long *) tx.mtext) = counter;
            msgsnd(msqID, &tx, SIZE_MSG, 0);
            printf("New client: %ld\n", counter);
            continue;
        }
        printf("Message from %ld: %s\n", txID, rx.mtext+8);
        tx = rx;
        for (tx.mtype = 3; tx.mtype <= counter; tx.mtype++) {
            if (tx.mtype == txID) {
                continue;
            }
            msgsnd(msqID, &tx, SIZE_MSG, 0);
        }
    }
    return 0;
}
