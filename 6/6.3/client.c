#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int sockfd;
    char sendline[1000];
    struct sockaddr_in servaddr, cliaddr;
    if(argc != 3){
        printf("Usage: ./5.1.client <IP address> <port>\n");
        exit(1);
    }
    
    if((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) < 0){
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
    
    printf("String => ");
    fgets(sendline, 1000, stdin);

    if(sendto(sockfd,
              sendline,
              strlen(sendline)+1,
              0,
              (struct sockaddr *) &servaddr,
              sizeof(servaddr)) < 0){
        perror(NULL);
        close(sockfd);
        exit(1);
    }

    close(sockfd);
    return 0;
}