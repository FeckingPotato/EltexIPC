#define MSG_CONNECT 1
#define MSG_DATA 2
#define MSG_EXIT 255
#define SIZE_MSG 128

struct msgbuf {
    int mtype;
    char text[SIZE_MSG];
};
