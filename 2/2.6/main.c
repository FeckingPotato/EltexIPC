#include <stdio.h>
#include <dirent.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>

char* getType(struct dirent* entry) {
    switch(entry->d_type) {
        case DT_BLK:
            return "block device";
        case DT_CHR:
            return "character device";
        case DT_DIR:
            return "directory";
        case DT_FIFO:
            return "named pipe (FIFO)";
        case DT_LNK:
            return "symbolic link";
        case DT_REG:
            return "regular file";
        case DT_SOCK:
            return "UNIX domain socket";
        default:
            return "unknown";
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Wrong amount of arguments\n");
        return 1;
    }
    char* dirName = malloc(256);
    memcpy(dirName, argv[1], 256);
    chdir(dirName);
    while (1) {
        DIR *directory = opendir(".");
        printf("Contents of '%s':\n", dirName);
        struct dirent *curEntry = readdir(directory);
        struct dirent **entryArr = malloc(0);
        int entryCounter = 0;
        while (curEntry != NULL) {
            entryCounter++;
            entryArr = realloc(entryArr, sizeof(struct dirent *) * entryCounter);
            entryArr[entryCounter - 1] = curEntry;
            printf("%d. %s, %s\n", entryCounter, curEntry->d_name, getType(curEntry));
            curEntry = readdir(directory);
        }
        printf("Pick a directory to go to (type 0 to exit): ");
        int input;
        scanf("%d", &input);
        if (input > entryCounter || input < 0) {
            printf("Wrong entry\n");
            continue;
        }
        if (input == 0) {
            return 0;
        }
        if (entryArr[input - 1]->d_type != DT_DIR) {
            printf("Not a directory\n");
            continue;
        }
        memcpy(dirName, entryArr[input - 1]->d_name, 256);
        chdir(dirName);
    }
}