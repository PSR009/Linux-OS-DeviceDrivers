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
int *p;

int main()
{
    int fd;

    fd = shm_open("/desdsem1", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(fd, sizeof(int));
    count_s = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    sem_t *sem1 = sem_open("/desdsem1", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    sem_t *sem2 = sem_open("/desdsem2", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);   
    sem_init(sem1, 1, 1); 

    //sem_wait(sem1);
    *count_s = 0;
    //sem_post(sem1);
    
    while (1)
    {
        printf("Send: before sem\n");
        sem_wait(sem2);
        (*count_s)++;
        printf("Sending count: %d\n", (*count_s));
        printf("Rcvd p: %d\n", (*p));
        sem_post(sem1);
        //sleep(1);
        printf("Send: after sem\n");
    }
}