#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFF_NO 2
#define BUFF_SIZE 10

void *T1(void *);
void *T2(void *);
void *T3(void *);

void creatBlock();
void destroyBloack();
int *getBlock(pthread_t);
void freeBlock(pthread_t);

sem_t devices;
int *buff[BUFF_NO];
int count1;
int count2;
pthread_t t_id1, t_id2;
