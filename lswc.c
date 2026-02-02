#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fds[2];
    pid_t pid;

    if (pipe(fds) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        dup2(fds[0], 0);
        close(fds[1]);
        execlp("wc", "wc", "-l", (char *)NULL);
        perror("execlp");
        exit(1);
    }

    dup2(fds[1], 1);
    close(fds[0]);

    if (argc == 2) {
        execlp("ls", "ls", "-1a", argv[1], (char *)NULL);
    } else {
        execlp("ls", "ls", "-1a", (char *)NULL);
    }

    perror("execlp");
    exit(1);
}