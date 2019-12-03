#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void *in_thread(void *);
void *proc_thread(void *);

sem_t sem_in_proc;
sem_t sem_proc_in;
int a, b;
