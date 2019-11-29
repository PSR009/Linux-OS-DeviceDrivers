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
    /*int g = mkfifo("/home/desd/Downloads/DESD_OS/fifo_add/desdfifo", 0600);
    if(-1 == g)
    {
        perror("Error opening mkfifo\n");
        exit(EXIT_FAILURE);
    }*/
    fds = open("desdfifo", O_WRONLY);
    if(-1 == fds)
    {
        perror("Error opening before write\n");
        exit(EXIT_FAILURE);
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
    write(fds, &a, sizeof(a));
    close(fds);
    fds = open("desdfifo", O_RDONLY);
    if(-1 == fds)
    {
        perror("Error opening before read\n");
        exit(EXIT_FAILURE);
    }
    read(fds, &b, sizeof(b));
    printf("Rcvd from user2: sum = %d\n", b);
    close(fds);
}