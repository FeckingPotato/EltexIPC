#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if(argc != 3){
        printf("Usage: ./5.2 <IP address> <port>\n");
        return 1;
    }
    int sockfd;
    char recvline[1000];
    struct sockaddr_in servaddr;
    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) < 0) {
        perror(NULL);
        return 1;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(strtol(argv[2], NULL, 10));
    if(inet_aton(argv[1], &servaddr.sin_addr) == 0) {
        printf("Invalid IP address\n");
        close(sockfd);
        exit(1);
    }
    unsigned int counter = 0;
    FILE *file;
    while (1) {
        ssize_t size = recvfrom(sockfd, recvline, 1000, 0, NULL, NULL);
        if(size < 0){
            perror(NULL);
            close(sockfd);
            return 0;
        }
        char path[32];
        sprintf(path, "packet%d.bin", counter);
        file = fopen(path, "w");
        fwrite(recvline, size, 1, file);
        fclose(file);
        if (recvline[9] == 0x11) {
            printf("%u. Received UDP message: %s\n",
                   counter, recvline+28);
        }
        else {
            printf("%u. Received non-UDP message\n", counter);
        }
        counter++;
    }
}
