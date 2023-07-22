#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Wrong amount of arguments\n");
        return 1;
    }
    int fileDesc = open(argv[1], O_WRONLY | O_APPEND);
    write(fileDesc, argv[2], strlen(argv[2]));
    close(fileDesc);
    return 0;
}