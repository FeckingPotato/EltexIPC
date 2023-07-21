#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Wrong amount of arguments\n");
        return 1;
    }
    FILE* file = fopen(argv[1], "r");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    char buffer[size+1];
    fread(buffer, 1, size, file);
    fclose(file);
    buffer[size] = '\0';
    printf("%s\n", buffer);
    return 0;
}