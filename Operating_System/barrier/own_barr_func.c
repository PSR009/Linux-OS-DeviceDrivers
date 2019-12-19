#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int count = 4;

void wait_func()
{
    count--;
    while (0 != count);
}

void *lcd(void *data)
{
    printf("LCD: Init_start\n");
    sleep(2);
    printf("LCD: Init_end\n");
    wait_func();
    printf("LCD: functionality_start\n");
}

void *serial(void *data)
{
    printf("serial: Init_start\n");
    sleep(7);
    printf("serial: Init_end\n");
    wait_func();
    printf("serial: functionality_start\n");
}

void *temp(void *data)
{
    printf("Temp.: Init_start\n");
    sleep(5);
    printf("Temp.: Init_end\n");
    wait_func();
    printf("Temp.: functionality_start\n");
}

void *network(void *data)
{
    printf("N/w: Init_start\n");
    sleep(10);
    printf("N/w: Init_end\n");
    wait_func();
    printf("N/w: functionality_start\n");
}

int main()
{
    pthread_t lcd_id, serial_id, temp_id, netw_id;

    pthread_create(&lcd_id, NULL, lcd, NULL);
    pthread_create(&serial_id, NULL, serial, NULL);
    pthread_create(&temp_id, NULL, temp, NULL);
    pthread_create(&netw_id, NULL, network, NULL);

    pthread_join(lcd_id, NULL);
    pthread_join(serial_id, NULL);
    pthread_join(temp_id, NULL);
    pthread_join(netw_id, NULL);

    return 0;
}