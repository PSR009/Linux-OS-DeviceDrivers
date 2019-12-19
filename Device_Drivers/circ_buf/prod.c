#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define BUFF_SIZE 8
String send_buff = "Hello";

int main()
{
    int fd, ret;
    fd = open("/dev/circ_buf", O_RDWR);
    if (fd < 0)
    {
        perror("\nError: Couldn't open device\n");
        return fd;
    }

    ret = write(fd, send_buff, strlen(send_buff));
    if (ret < 0)
    {
        perror("\nError: Couldn't write to device\n");
        return ret;
    }
    printf("\nWrote %d bytes\n", ret);
    return 0;
}