#include "rec_mutex.h"

int count = 0;
int main()
{
    pthread_t incId, decId;

    pthread_create(&incId, NULL, incThread, NULL);
    pthread_create(&decId, NULL, decThread, NULL);

    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
    pthread_mutex_init(&countMutex, &attr);

    pthread_join(incId, NULL);
    pthread_join(decId, NULL);

    pthread_mutex_destroy(&countMutex);
    pthread_mutexattr_destroy(&attr);
}