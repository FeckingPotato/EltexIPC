#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
void error(const char *msg) {
    perror(msg);
    exit(0);
}
int main(int argc, char *argv[]) {
    int my_sock, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buff[1024];
    printf("TCP DEMO CLIENT\n");
    if (argc < 4) {
        fprintf(stderr, "usage %s hostname port filepath\n",
                argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);
    
    my_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (my_sock < 0) error("ERROR opening socket");

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr,
          server->h_length);

    serv_addr.sin_port = htons(portno);
    
    if (connect(my_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    if ((n = recv(my_sock, &buff[0], sizeof(buff) - 1, 0)) > 0) {
        if (buff[0] != 'R') {
            printf("Unable to connect\n");
            close(my_sock);
            return 0;
        }
        FILE *file = fopen(argv[3], "r");
        fseek(file, 0, SEEK_END);
        unsigned int size = ftell(file);
        rewind(file);
        char *data = malloc(size);
        fread(data, size, 1, file);
        fclose(file);
        send(my_sock, data, size, 0);
    }
    close(my_sock);
    return 0;
}