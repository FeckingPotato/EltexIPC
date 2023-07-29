#define SERVER_ID 1
#define HANDSHAKE_ID 2
#define SIZE_MSG 512

struct msgbuf {
    long mtype;
    char mtext[SIZE_MSG];
};
