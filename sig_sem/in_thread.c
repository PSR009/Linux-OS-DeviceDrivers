#include "sig_sem.h"

void *in_thread(void *data)
{
    while(1)
    {
        sem_wait(&sem_proc_in);
        printf("Enter a:");
        scanf("%d",&a);
        printf("Enter b:");
        scanf("%d",&b);
        printf("In_thread: a = %d b = %d\n", a, b);
        sem_post(&sem_in_proc);
    }
}