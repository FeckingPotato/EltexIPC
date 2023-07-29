#pragma once
#define MSG_CONNECT 1
#define MSG_DATA 2
#define MSG_EXIT 255
#define SIZE_MSG 512

struct msgbuf {
    long mtype;
    char text[SIZE_MSG];
};
