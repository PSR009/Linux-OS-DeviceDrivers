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
int *p;

int main()
{
    sem_t *sem1 = sem_open("/desdsem1", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    sem_t *sem2 = sem_open("/desdsem2", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    sem_init(sem2, 1, 0);

    int fd1, fd2;

    fd1 = shm_open("/desdsem1", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(fd1, sizeof(int));
    count_r = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);

    fd2 = shm_open("/desdsem2", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(fd2, sizeof(int));
    p = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);

    //sem_post(sem2);
    *p = 50;
    //sem_wait(sem2);

    while (1)
    {
        printf("Recvd: before sem\n");
        sem_wait(sem1);
        (*p)++;
        printf("Sending p: %d\n", (*p));
        printf("Rcvd count: %d\n", (*count_r));
        sem_post(sem2);
        //sleep(1);
        printf("Recvd: after sem\n");
    }
}