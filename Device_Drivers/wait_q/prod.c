#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFF_SIZE 8
char send_buff[BUFF_SIZE] = "Hello";

int main()
{
    int fd, ret;
    fd = open("/dev/wait_q", O_RDWR);
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