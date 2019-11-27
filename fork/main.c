#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    printf("-----------Before fork\n");
    printf("PID: %d\n", getpid());
    printf("PPID: %d\n", getppid());
    fork();
    printf("----------After fork\n");
    printf("PID: %d\n", getpid());
    printf("PPID: %d\n", getppid());
    /*
    fork();
    printf("-----After 2 forks\n");
    printf("PPID ID: %d\n", getppid());
    printf("PID ID: %d\n", getpid());*/
}