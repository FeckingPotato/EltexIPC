#include <stdio.h>
#include <dirent.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Wrong amount of arguments\n");
        return 1;
    }
    DIR* directory = opendir(argv[1]);
    printf("Contents of '%s' :\n", argv[1]);
    struct dirent* curEntry = readdir(directory);
    while (curEntry != NULL) {
        printf("%s\n", curEntry->d_name);
        curEntry = readdir(directory);
    }
    return 0;
}