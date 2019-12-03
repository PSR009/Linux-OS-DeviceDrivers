#include "count.h"

int count = 0; 
int main()
{
    pthread_t incId, decId;

    pthread_create(&incId, NULL, incThread, NULL);
    pthread_create(&decId, NULL, decThread, NULL);

    pthread_mutex_init(&countMutex, NULL);

    pthread_join(incId, NULL);
    pthread_join(decId, NULL);
    
    pthread_mutex_destroy(&countMutex);
    return 0;
}