#define MSG_CONNECT 1
#define MSG_SERVER 2
#define MSG_CLIENT 3
#define MSG_EXIT 255
#define SIZE_MSG 512

struct msgbuf {
    int mtype;
    char text[SIZE_MSG];
};
