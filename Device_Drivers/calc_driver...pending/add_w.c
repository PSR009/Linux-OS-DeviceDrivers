#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

struct calc
{
    int a;
    int b;
} *add;

int main()
{
    int fd, ret;
    fd = open("/dev/AddDev", O_RDWR);
    if (fd < 0)
    {
        perror("\nError: Couldn't open Add device\n");
        return fd;
    }

    add->a = 5;
    add->b = 3;

    ret = write(fd, (char *)add,  sizeof(struct calc));
    if (ret < 0)
    {
        perror("\nError: Couldn't write to Add device\n");
        return ret;
    }
    printf("\nAddDev: Wrote %d bytes\n", ret);
    return 0;
}