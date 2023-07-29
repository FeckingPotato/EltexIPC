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
    if (msgsnd(msqID, &tx, SIZE_MSG, 0) == -1) {
        perror("Unable to access the queue");
        return 1;
    }
    msgrcv(msqID, &rx, SIZE_MSG, HANDSHAKE_ID, 0);
    long ID = *((long *) rx.mtext);
    *((long *) tx.mtext) = ID;
    printf("Connected, your ID: %ld\n", ID);
    stdin->_IO_read_ptr = stdin->_IO_read_end;
    pid_t pid;
    switch (pid = fork()) {
        case -1:
            perror("Unable to fork");
            return 1;
        case 0:
            while (!done) {
                msgrcv(msqID, &rx, SIZE_MSG, ID, 0);
                printf("\nClient #%ld: %s\n", *((long *) rx.mtext), rx.mtext+8);
                fflush(stdin);
            }
            return 0;
        default:
            signal(SIGINT, exitFunc);
            while (!done) {
                printf("Your input: ");
                tx.mtype = SERVER_ID;
                fgets(tx.mtext+8, SIZE_MSG - 8, stdin);
                msgsnd(msqID, &tx, SIZE_MSG, 0);
            }
            kill(pid, 9);
            return 0;
    }
}