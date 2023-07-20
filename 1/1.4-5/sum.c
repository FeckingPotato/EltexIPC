#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    long first = strtol(argv[0], NULL, 10);
    long second = strtol(argv[1], NULL, 10);
    printf("%d\n", first+second);
    return 0;
}
