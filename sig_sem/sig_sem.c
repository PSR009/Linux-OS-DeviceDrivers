#include "sig_sem.h"

int main()
{
    pthread_t in_id, proc_id;
    sem_init(&sem_in_proc, 0, 0);
    sem_init(&sem_proc_in, 0, 1);

    pthread_create(&in_id, NULL, in_thread, NULL);
    pthread_create(&proc_id, NULL, proc_thread, NULL);

    pthread_join(in_id, NULL);
    pthread_join(proc_id, NULL);

    sem_destroy(&sem_in_proc);
    sem_destroy(&sem_proc_in);
    return 0;
}