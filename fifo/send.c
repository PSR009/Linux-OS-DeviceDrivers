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
    int fds;
    fds = open("desdfifo", O_WRONLY);
    if(fds == -1)
    {
        perror("Error opening the file\n");
        exit(EXIT_FAILURE);
    }
    write(fds, "Hello\n", 6);
    close(fds);
}