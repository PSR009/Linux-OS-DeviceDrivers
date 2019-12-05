#include "count_sem.h"

int count1 = 1;
int count2 = 1;
int *getBlock(pthread_t t_id)
{
    sem_wait(&devices);
    if (count1)
    {
        count1--;
        t_id1 = t_id;
        return buff[1];
    }
    else if (count2)
    {
        count2--;
        t_id2 = t_id;
        return buff[2];
    }
    else
        return NULL;
}

void createBlock()
{
    for (int i = 0; i < BUFF_NO; i++)
    {
        buff[i] = (int *)malloc(BUFF_SIZE);
        if (!buff[i])
        {
            fprintf(stderr, "Couldn't allocate\n");
        }
    }
    printf("Blocks created: %d\n", BUFF_NO);
}

void freeBlock(pthread_t t_id)
{
    if (t_id == t_id1)
    {
        sem_post(&devices);
        //t_id1 = NULL;
        count1++;
    }
    else if (t_id == t_id2)
    {
        sem_post(&devices);
        count2++;
    }
}

void destroyBlock()
{
    for (int i = 0; i < BUFF_NO; i++)
    {
        free(buff[i]);
        //buff[i] = NULL;
    }
    printf("Blocks destroyed: %d\n", BUFF_NO);
}

int main()
{
    pthread_t id1, id2, id3;
    createBlock();

    sem_init(&devices, 0, BUFF_NO);

    pthread_create(&id1, NULL, T1, NULL);
    pthread_create(&id2, NULL, T2, NULL);
    pthread_create(&id3, NULL, T3, NULL);

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
    pthread_join(id3, NULL);

    sem_destroy(&devices);
    destroyBlock();
    return 0;
}