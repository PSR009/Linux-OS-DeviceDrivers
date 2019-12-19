#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
    pid_t id;
    printf("-----------Before fork\n");
    printf("PID: %d\n", getpid());
    printf("PPID: %d\n", getppid());
    printf("-----------After fork\n");
    id = fork();
    if(0 == id)
    {
        printf("CHILD: PID: %d PPID: %d\n", getpid(), getppid());
    }
    else
    {
        printf("PARENT: PID: %d PPID: %d\n", getpid(), getppid());
    }
    return 0;
}