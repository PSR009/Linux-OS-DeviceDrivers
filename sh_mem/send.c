#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int *count_s;
int main()
{
    int fd;
    fd = shm_open("/desdshm", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(fd, sizeof(int));
    count_s = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    *count_s = 0;
    while (1)
    {
        (*count_s)++;
        printf("Sending count: %d\n", (*count_s));
        sleep(1);
    }
}