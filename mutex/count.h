#include <stdio.h>
#include <pthread.h>
void *incThread(void *);
void *decThread(void *);
int count;
pthread_mutex_t countMutex;
