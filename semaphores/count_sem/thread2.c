#include "count_sem.h"

void *T2(void *data)
{
    while(1)
    {
        pthread_t t2_id;
        t2_id = pthread_self();
        int *arr2 = getBlock(t2_id);
        printf("T2 got block with id: %ld\n", t2_id);
        sleep(5);
        freeBlock(t2_id);
        printf("T2 freed block with id: %ld\n", t2_id);
    }
}