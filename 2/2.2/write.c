#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Wrong amount of arguments\n");
        return 1;
    }
    FILE* file = fopen(argv[1], "a");
    fwrite(argv[2], 1, strlen(argv[2]), file);
    fclose(file);
    return 0;
}