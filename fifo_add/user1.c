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
    int a[2] = {3,4}, b;
    fds = open("desdfifo", O_WRONLY);
    if(-1 == fds)
    {
        perror("Error opening the file\n");
        exit(EXIT_FAILURE);
    }
    write(fds, &a, 8);
    close(fds);
    fds = open("desdfifo", O_RDONLY);
    if(-1 == fds)
    {
        perror("Error opening the file\n");
        exit(EXIT_FAILURE);
    }
    read(fds, &b, 4);
    printf("Rcvd from user2: sum = %d\n", b);
    close(fds);
}