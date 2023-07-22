#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Wrong amount of arguments\n");
        return 1;
    }
    if (access(argv[1], F_OK) != 0) {
        printf("%s does not exist. Should it be created? (y/n)\n", argv[1]);
        char input = getchar();
        if (input != 'y' && input != 'Y') {
            printf("Aborting\n");
            return 0;
        }
    }
    FILE* file = fopen(argv[1], "a");
    fwrite(argv[2], 1, strlen(argv[2]), file);
    fclose(file);
    return 0;
}