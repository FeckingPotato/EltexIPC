#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int sockfd;
    char sendline[1000], recvline[1000]; 
    struct sockaddr_in servaddr, cliaddr;
    unsigned int id;
    if(argc != 3){
        printf("Usage: ./5.1.client <IP address> <port>\n");
        exit(1);
    }
    
    if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
        perror(NULL); 
        exit(1);
    }

    bzero(&cliaddr, sizeof(cliaddr));
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(0);
    cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, (struct sockaddr *) &cliaddr, sizeof(cliaddr)) < 0){
        perror(NULL);
        close(sockfd); 
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(strtol(argv[2], NULL, 10));
    if(inet_aton(argv[1], &servaddr.sin_addr) == 0) {
        printf("Invalid IP address\n");
        close(sockfd); 
        exit(1);
    }
    if(sendto(sockfd, "N", 1, 0, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) { // handshake begin
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    if((recvfrom(sockfd, &id, 4, 0, (struct sockaddr *) NULL, NULL)) < 0) { // handshake end
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    char recMessage[1000];
    switch(fork()) {
        case -1:
            perror("fork error");
            close(sockfd);
            exit(1);
        case 0:
            while (1) {
                if((recvfrom(sockfd, &recMessage, 1000, 0, (struct sockaddr *) NULL, NULL)) < 0) { // handshake end
                    perror(NULL);
                    close(sockfd);
                    exit(1);
                }
                printf("%s\n", recMessage);
                fflush(stdin);
            }
        default:
            while (1) {
                unsigned int recID;
                printf("Your id: %u\n"
                       "Input id of the recipient: ", id);
                scanf("%u", &recID);
                stdin->_IO_read_ptr = stdin->_IO_read_end;
                printf("Enter your message: ");
                fgets(sendline, 1000, stdin);
                char* message = malloc(1005);
                message[0] = 'O';
                *((unsigned int *) &(message[1])) = recID;
                strcpy(&(message[5]), sendline);
                if (sendto(sockfd, message, strlen(sendline) + 6, 0, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
                    perror(NULL);
                    close(sockfd);
                    exit(1);
                }
            }
    }
}