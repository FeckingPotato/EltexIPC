#include <stdio.h>
#include <malloc.h>
#include "posixPort.h"

mqd_t msgget(int id, int flags) {
    char path[32];
    sprintf(path, "/MQueue%d", id);
    struct mq_attr attr;
    attr.mq_maxmsg = 32;
    attr.mq_msgsize = SIZE_MSG;
    return mq_open(path, flags | O_RDWR, 0666, &attr);
}

ssize_t msgrcv(mqd_t fd, struct msgbuf *buf, size_t size, long mtype, int flags) {
    buf = malloc(sizeof(struct msgbuf));
    ssize_t recSize;
    while (1) {
        recSize = mq_receive(fd, buf->text, size, &buf->mtype);
        if (buf->mtype == mtype || mtype == 0 || recSize == -1) {
            break;
        }
        mq_send(fd, buf->text, size, buf->mtype);
        if (flags == IPC_NOWAIT) {
            return 0;
        }
    }
    return recSize;
}

int msgsnd(mqd_t fd, struct msgbuf *buf, size_t size, int flags) {
    return mq_send(fd, buf->text, size, buf->mtype);
}