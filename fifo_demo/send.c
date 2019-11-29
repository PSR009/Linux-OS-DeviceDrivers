#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#define BUFF_SIZE 4096

int main(int argc, char *argv[])
{
    int fds;
    char buf1[BUFF_SIZE];
    fds = open("desdfifo", O_WRONLY);
    if(-1 == fds)
    {
        perror("Error opening the file\n");
        exit(EXIT_FAILURE);
    }
    write(fds, "Hello\n", 6);
    close(fds);
    fds = open("desdfifo", O_RDONLY);
    if(-1 == fds)
    {
        perror("Error opening the file\n");
        exit(EXIT_FAILURE);
    }
    read(fds, buf1, BUFF_SIZE);
    printf("Rcvd from user2: %s\n", buf1);
    close(fds);
}