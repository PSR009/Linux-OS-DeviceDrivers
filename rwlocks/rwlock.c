#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

int count = 0;
pthread_rwlock_t rw_lock;

void err_check(int err, char perr[])
{
    if (0 != err)
    {
        printf("Error: %s: ", perr);
        perror("\n");
        exit(EXIT_FAILURE);
    }
}

void *write_1(void *data)
{
    while (1)
    {  
        pthread_rwlock_wrlock(&rw_lock);
        printf("write_1: locked\n");
        count++;
        //printf("write_1: inc: %d\n", count);
        sleep(2);
        pthread_rwlock_unlock(&rw_lock);
        printf("write_1: unlocked\n");
    }
}

void *write_2(void *data)
{
    while (1)
    {
        pthread_rwlock_wrlock(&rw_lock);
        printf("write_2: locked\n");
        count++;
        //printf("write_2: inc: %d\n", count);
        sleep(4);
        pthread_rwlock_unlock(&rw_lock);
        printf("write_2: unlocked\n");
    }
}

void *read_1(void *data)
{
    while (1)
    {
        pthread_rwlock_rdlock(&rw_lock);
        printf("read_1: locked\n");
        //printf("read_1: count = %d\n", count);
        sleep(1);
        pthread_rwlock_unlock(&rw_lock);
        printf("read_1: unlocked\n");
    }
}

void *read_2(void *data)
{
    while (1)
    {
        pthread_rwlock_rdlock(&rw_lock);
        printf("read_2: locked\n");
        int add = count + 10;
        //printf("read_2: add = %d \n", add);
        sleep(3);
        pthread_rwlock_unlock(&rw_lock);
        printf("read_2: unlocked\n");
    }
}

int main()
{
    pthread_t rd1, rd2, wr1, wr2;
    int err;
    pthread_rwlock_init(&rw_lock, NULL);

    err = pthread_create(&rd1, NULL, read_1, NULL);
    err_check(err, "Creating thread: read1");

    err = pthread_create(&rd2, NULL, read_2, NULL);
    err_check(err, "Creating thread: read2");

    err = pthread_create(&wr1, NULL, write_1, NULL);
    err_check(err, "Creating thread: write1");

    err = pthread_create(&wr2, NULL, write_2, NULL);
    err_check(err, "Creating thread: write2");

    err = pthread_join(rd1, NULL);
    err_check(err, "Joining thread: read1");
    
    err = pthread_join(rd2, NULL);
    err_check(err, "Joining thread: read2");
    
    err = pthread_join(wr1, NULL);
    err_check(err, "Joining thread: write1");

    err = pthread_join(wr2, NULL);
    err_check(err, "Joining thread: write2");
    
    pthread_rwlock_destroy(&rw_lock);

    return 0;
}