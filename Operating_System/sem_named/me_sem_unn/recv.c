#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int *count_r;

int main()
{
    int fd;

    fd = shm_open("/desdshm", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(fd, sizeof(int));
    count_r = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    sem_t *sem = sem_open("/desdshm", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    sem_init(sem, 1, 1);

    while (1)
    {
        printf("Recvd: before sem\n");
        sem_wait(sem);
        printf("Recvd: %d\n", (*count_r));
        sem_post(sem);
        sleep(1);
        printf("Recvd: after sem\n");
    }
}