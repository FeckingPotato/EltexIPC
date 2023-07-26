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
    char msg[1000];
    struct sockaddr_in servaddr, cliaddr;
    unsigned int clientCounter = 0;
    struct sockaddr_in* clients = malloc(sizeof(struct sockaddr_in));

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(strtol(argv[1], NULL, 10));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
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

        if ((recvfrom(sockfd, msg, 999, 0,
                      (struct sockaddr *) &cliaddr, &clilen)) < 0) {
            perror(NULL);
            close(sockfd);
            exit(1);
        }
        if (msg[0] == 'N') { // "N" - new client message
            sendto(sockfd, &clientCounter, sizeof(unsigned int), 0, (struct sockaddr *) &cliaddr, clilen);
            clients[clientCounter] = cliaddr;
            clientCounter++;
            clients = realloc(clients, sizeof(struct sockaddr_in)*(clientCounter+1));
            continue;
        }
        if (msg[0] == 'O') { // "O"+uint - outbound client message
            unsigned int id = *((unsigned int *) &(msg[1]));
            if (id >= clientCounter) {
                sendto(sockfd, "\nErr: No such client\n", 21, 0, (struct sockaddr *) &cliaddr, clilen);
                continue;
            }
            char strID[11];
            sprintf(strID, "%u", id);
            char* message = malloc(strlen(&(msg[1]))+3+strlen(strID));
            strcpy(message, "\nC");
            strcpy(&(message[2]), strID);
            strcpy(&(message[2+strlen(strID)]), ": ");
            strcpy(&(message[4+strlen(strID)]), &(msg[5]));
            sendto(sockfd, message, strlen(message)+1, 0, (struct sockaddr *) &clients[id], sizeof(clients[id]));
        }
    }
}