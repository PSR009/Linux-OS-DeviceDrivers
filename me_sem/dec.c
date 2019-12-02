#include "me_sem.h"

void *decThread(void *data)
{
    while(1)
    {
        sem_wait(&sem_count);
        count--;
        printf("Dec: %d\n",count);
        sem_post(&sem_count);
    }
}