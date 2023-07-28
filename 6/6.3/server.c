#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: ./5.1server <port>\n");
        return 0;
    }
    int sockfd;
    unsigned int clilen;
    char line[1000];
    struct sockaddr_in servaddr, cliaddr;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(strtol(argv[1], NULL, 10));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) < 0){
        perror(NULL);
        exit(1);
    }

    if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror(NULL);
        close(sockfd);
        exit(1);
    }

    while (1) {

        clilen = sizeof(cliaddr);

        if ((recvfrom(sockfd, line, 999, 0,
                      (struct sockaddr *) &cliaddr, &clilen)) < 0) {
            perror(NULL);
            close(sockfd);
            exit(1);
        }

        printf("%s\n", line+20);
    }
}