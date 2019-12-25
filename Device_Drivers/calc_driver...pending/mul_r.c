#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFF_SIZE 16
char recv_buff[BUFF_SIZE];

int main()
{
    int fd, ret;
    fd = open("/dev/MulDev", O_RDWR);
    if (fd < 0)
    {
        perror("\nError: Couldn't open Mul device\n");
        return fd;
    }

    ret = read(fd, recv_buff, BUFF_SIZE);
    if (ret < 0)
    {
        perror("Error: Couldn't read from Mul device\n");
        return ret;
    }
    printf("\nMulDev: Read %d bytes : %s\n", ret, recv_buff);
    return 0;
}