#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int *count_s;

int main()
{
    int fd;
    fd = shm_open("/desdshm", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    ftruncate(fd, sizeof(int));
    count_s = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    sem_t *sem = sem_open("/desdshm", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    sem_init(sem, 1, 1);  

    sem_wait(sem);
    *count_s = 0;
    sem_post(sem);

    while (1)
    {
        printf("Send: before sem\n");
        sem_wait(sem);
        (*count_s)++;
        printf("Sending: %d\n", (*count_s));
        sleep(1);
        sem_post(sem);
        printf("Send: after sem\n");
    }
}