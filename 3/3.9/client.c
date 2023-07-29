#include <stdio.h>
#include <signal.h>
#include <sys/msg.h>
#include <unistd.h>
#include "msgStruct.h"

int done = 0;

void exitFunc(int) {
    done = 1;
}

int main() {
    int msqID;
    printf("Input the message queue ID: ");
    scanf("%d", &msqID);
    struct msgbuf rx, tx;
    tx.mtype = SERVER_ID;
    tx.txID = 0;
    if (msgsnd(msqID, &tx, SIZE_MSG, 0) == -1) {
        perror("Unable to access the queue");
        return 1;
    }
    msgrcv(msqID, &rx, SIZE_MSG, HANDSHAKE_ID, 0);
    tx.txID =  *((int *) rx.text);
    printf("Connected, your ID: %d\n", tx.txID);
    stdin->_IO_read_ptr = stdin->_IO_read_end;
    pid_t pid;
    switch (pid = fork()) {
        case -1:
            perror("Unable to fork");
            return 1;
        case 0:
            while (!done) {
                msgrcv(msqID, &rx, SIZE_MSG, tx.txID, 0);
                printf("\nClient #%d: %s\n", rx.txID, rx.text);
                fflush(stdin);
            }
            return 0;
        default:
            signal(SIGINT, exitFunc);
            while (!done) {
                printf("Your input: ");
                fgets(tx.text, SIZE_MSG-4, stdin);
                msgsnd(msqID, &tx, SIZE_MSG, 0);
            }
            kill(pid, 9);
            return 0;
    }
}