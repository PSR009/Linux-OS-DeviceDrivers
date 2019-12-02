#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void *incThread(void *);
void *decThread(void *);

sem_t sem_count;
int count;
