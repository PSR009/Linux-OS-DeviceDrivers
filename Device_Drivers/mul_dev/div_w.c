#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFF_SIZE 16
char send_buff[BUFF_SIZE] = "Division";

int main()
{
    int fd, ret;
    fd = open("/dev/DivDev", O_RDWR);
    if (fd < 0)
    {
        perror("\nError: Couldn't open Div device\n");
        return fd;
    }

    ret = write(fd, send_buff, strlen(send_buff));
    if (ret < 0)
    {
        perror("\nError: Couldn't write to Div device\n");
        return ret;
    }
    printf("\nDivDev: Wrote %d bytes\n", ret);
    return 0;
}