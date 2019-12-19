#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFF_SIZE 8
char recv_buff[BUFF_SIZE];

int main()
{
    int fd, ret;
    fd = open("/dev/wait_q", O_RDWR);
    if (fd < 0)
    {
        perror("\nError: Couldn't open device\n");
        return fd;
    }
    
    ret = read(fd, recv_buff, BUFF_SIZE);
    if (ret < 0)
    {
        perror("Error: Couldn't read from device\n");
        return ret;
    }
    printf("\nRead %d bytes : %s\n", ret, recv_buff);
    return 0;
}