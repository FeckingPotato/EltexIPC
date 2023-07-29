#pragma once
#include <mqueue.h>
#include "msgStruct.h"

#define IPC_PRIVATE 310
#define IPC_CREAT O_CREAT
#define IPC_NOWAIT O_NONBLOCK

mqd_t msgget(int id, int flags);

ssize_t msgrcv(mqd_t fd, struct msgbuf *buf, size_t size, long mtype, int flags);

int msgsnd(mqd_t fd, struct msgbuf *buf, size_t size, int flags);

