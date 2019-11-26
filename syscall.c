#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
int main(int argc, char *argv[])
{
    int fd;
    fd = open("desd.log", O_RDWR | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH);
    if(fd == -1)
    {
        perror("Error opening the file\n");
        exit(EXIT_FAILURE);
    }
    write(fd, "Hello\n", 6);
    write(fd, "World\n", 6);
    close(fd);
    return 0;
}