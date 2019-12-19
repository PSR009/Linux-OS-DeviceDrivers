#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFF_SIZE 1024
char send_buff[BUFF_SIZE] = "Hello Mr.Beast!\n";
char recv_buff[BUFF_SIZE];

int main()
{
    int fd, err;
    fd = open("/dev/teststat", O_RDWR);
    if (fd < 0)
    {
        perror("\nError: Couldn't open device\n");
        return fd;
    }

    write(fd, send_buff, strlen(send_buff));
    printf("\nWriting to device\n");
    
    err = read(fd, recv_buff, BUFF_SIZE);
    if (err < 0)
    {
        perror("Error: Couldn't read\n");
        return err;
    }
    printf("\nReading from device: %s\n", recv_buff);

    return 0;
}