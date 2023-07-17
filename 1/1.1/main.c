#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid = getpid();
    printf("PID: %d\n", pid);
    printf("PPID: %d\n", getppid());
    printf("UID: %d\n", getuid());
    printf("EUID: %d\n", geteuid());
    printf("GID: %d\n", getgid());
    printf("SID: %d\n", getsid(pid));
    return 0;
}
