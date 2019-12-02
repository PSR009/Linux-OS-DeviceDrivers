#include "me_sem.h"

void *incThread(void *data)
{
    while(1)
    {
        sem_wait(&sem_count);
        count++;
        printf("Inc: %d\n",count);
        sem_post(&sem_count);
    }
}