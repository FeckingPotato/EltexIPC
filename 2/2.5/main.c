#include <stdio.h>
#include <dirent.h>

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
    DIR* directory = opendir(argv[1]);
    printf("Contents of '%s' :\n", argv[1]);
    struct dirent* curEntry = readdir(directory);
    while (curEntry != NULL) {
        printf("%s, %s\n", curEntry->d_name, getType(curEntry));
        curEntry = readdir(directory);
    }
    return 0;
}