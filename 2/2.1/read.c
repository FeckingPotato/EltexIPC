#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Wrong amount of arguments\n");
        return 1;
    }
    int fileDesc = open(argv[1], O_RDONLY);
    long size = lseek(fileDesc, 0, SEEK_END);
    lseek(fileDesc, 0, SEEK_SET);
    char buffer[size+1];
    read(fileDesc, buffer, size);
    close(fileDesc);
    buffer[size] = '\0';
    printf("%s\n", buffer);
    return 0;
}