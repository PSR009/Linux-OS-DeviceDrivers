#include "count.h"

void *incThread(void *data)
{
    while(1)
    {
        pthread_mutex_lock(&countMutex);
        count++;
        printf("Inc: %d\n",count);
        pthread_mutex_unlock(&countMutex);
    }
}