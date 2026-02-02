#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fd;

    if (argc < 3) {
        printf("usage: redirout filename command [arg1 [arg2 ... ] ]\n");
        exit(1);
    }

    fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    dup2(fd, 1);
    close(fd);

    execvp(argv[2], &argv[2]);
    perror("execvp");
    exit(1);
}