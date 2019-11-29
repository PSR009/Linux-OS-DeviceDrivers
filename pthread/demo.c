#include <stdio.h>
#include <pthread.h>

void *rtc_thread(void *data)
{
    printf("Inside thread\n");
}
int main()
{
    pthread_t id_rtc;
    printf("Before thread creation\n");
    pthread_create(&id_rtc, NULL, rtc_thread, NULL);
    pthread_join(id_rtc, NULL);
    printf("After thread joining\n");
}