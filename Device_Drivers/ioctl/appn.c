#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include "my_ioctl.h"

int main()
{
    int fd, ret, k = 10, l;
    
    fd = open("/dev/my_ioctl", O_RDWR);
    if (fd < 0)
    {
        perror("\nError: Couldn't open device\n");
        return fd;
    }

    ioctl(fd, CMD_1);
    ioctl(fd, CMD_GET, &k);
    ioctl(fd, CMD_POST, &l);
    
    printf("\nRead from kernel: %d \n", l);
    return 0;
}