#include "sig_sem.h"

void *proc_thread(void *data)
{
    int sum = 0;
    while(1)
    {
        sem_wait(&sem_in_proc);
        sum = a + b;
        printf("proc_thread: sum = %d\n", sum);
        sem_post(&sem_proc_in);
    }
}