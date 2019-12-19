#include <stdio.h>
#include <pthread.h>

void *incThread(void *);
void *decThread(void *);

pthread_mutexattr_t attr;
pthread_mutex_t countMutex;
int count;
