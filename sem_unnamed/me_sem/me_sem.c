#include "me_sem.h"

int count = 0;

int main()
{
    pthread_t incId, decId;
    sem_init(&sem_count, 0, 1);

    pthread_create(&incId, NULL, incThread, NULL);
    pthread_create(&decId, NULL, decThread, NULL);

    pthread_join(incId, NULL);
    pthread_join(decId, NULL);

    sem_destroy(&sem_count);
    return 0;
}