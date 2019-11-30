#include <stdio.h>
#include <pthread.h>
int count = 0;
pthread_mutex_t countMutex;

void *incThread(void *data)
{
    while(1)
    {
        count++;
        printf("Inc: %d\n",count);
    }
}

void *decThread(void *data)
{
    while(1)
    {
        count--;
        printf("Dec: %d\n",count);
    }
}

int main()
{
    pthread_t incId, decId;
    pthread_create(&incId, NULL, incThread, NULL);
    pthread_create(&decId, NULL, decThread, NULL);
    pthread_mutex_init(&countMutex, NULL);
    pthread_join(incId, NULL);
    pthread_join(decId, NULL);
    pthread_mutex_destroy(&countMutex);
}