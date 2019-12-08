#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int event = 0;
pthread_mutex_t event_mutex;
pthread_cond_t event_cond_var;

void *wait_thread(void *data)
{
    int err1, err2;
    printf("Wait_event: before lock\n");
    err1 = pthread_mutex_lock(&event_mutex);
    if (0 != err1)
    {
        perror("Error: wait mut_lock\n");
        exit(EXIT_FAILURE);
    }
    printf("Wait_event: Grabbed Mutex\n");

    printf("Wait_event: waiting\n");
    while (event != 1)
    {
        printf("Wait_event: before condvar wait\n");
        pthread_cond_wait(&event_cond_var, &event_mutex);
        printf("Wait_event: after condvar wait\n");
    }
    
    err2 = pthread_mutex_unlock(&event_mutex);
    if (0 != err2)
    {
        perror("Error: wait mut_unlock\n");
        exit(EXIT_FAILURE);
    }
    printf("Wait_event: mutex unlock\n");
}

void *setter_thread(void *data)
{
    int err1, err2;
    printf("Setter_event: before lock\n");
    sleep(2);
    err1 = pthread_mutex_lock(&event_mutex);
    if (0 != err1)
    {
        perror("Error: eve mut_lock\n");
        exit(EXIT_FAILURE);
    }
    printf("Setter_event: Grabbed Mutex\n");

    event = 1;
    printf("Setter_event: event = 1\n");

    pthread_cond_signal(&event_cond_var);
    printf("Setter_event: signaling to cond_wait\n");

    err2 = pthread_mutex_unlock(&event_mutex);
    if (0 != err2)
    {
        perror("Error: eve mut_lock\n");
        exit(EXIT_FAILURE);
    }
    printf("Setter_event: Mutex unlock\n");
    //pthread_cond_signal(&event_cond_var);
    //printf("Setter_event: signaling to cond_wait\n");
}

int main()
{
    pthread_t wait_id, set_id;
    int err1, err2, err3, err4;
    
    pthread_mutex_init(&event_mutex, NULL);
    pthread_cond_init(&event_cond_var, NULL);
    
    err1 = pthread_create(&wait_id, NULL, wait_thread, NULL);
    if (0 != err1)
    {
        perror("Error: wait th_create\n");
        exit(EXIT_FAILURE);
    }
    err2 = pthread_create(&set_id, NULL, setter_thread, NULL);
    if (0 != err2)
    {
        perror("Error: event th_create\n");
        exit(EXIT_FAILURE);
    }
    
    err3 = pthread_join(wait_id, NULL);
    if (0 != err3)
    {
        perror("Error: wait th_joinig\n");
        exit(EXIT_FAILURE);
    }

    err4 = pthread_join(set_id, NULL);
    if (0 != err4)
    {
        perror("Error: eve th_joinig\n");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_destroy(&event_mutex);

    return 0;
}