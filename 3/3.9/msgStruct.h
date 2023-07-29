#define SERVER_ID 1
#define HANDSHAKE_ID 2
#define SIZE_MSG 512

struct msgbuf {
    int mtype;
    int txID;
    char text[SIZE_MSG-4];
};
