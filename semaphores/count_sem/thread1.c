#include "count_sem.h"

void *T1(void *data)
{
    while (1)
    {
        pthread_t t1_id;
        t1_id = pthread_self();
        int *arr1 = getBlock(t1_id);
        printf("T1 got block with id: %ld\n", t1_id);
        sleep(4);
        freeBlock(t1_id);
        printf("T1 freed block with id: %ld\n", t1_id);
    }
}