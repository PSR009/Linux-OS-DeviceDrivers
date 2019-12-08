#include "count_sem.h"

void *T3(void *data)
{
    while (1)
    {
        pthread_t t3_id;
        t3_id = pthread_self();
        int *arr3 = getBlock(t3_id);
        printf("T3 got block with id: %ld\n", t3_id);
        sleep(2);
        freeBlock(t3_id);
        printf("T3 freed block with id: %ld\n", t3_id);
    }
}