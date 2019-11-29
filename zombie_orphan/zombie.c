#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
    pid_t id;
    printf("-----------Before fork\n");
    id = fork();
    if(0 == id)
    {
        printf("CHILD: PID: %d PPID: %d\n", getpid(), getppid());
        //exit(0);
    }
    else
    {
        printf("PARENT: PID: %d PPID: %d\n", getpid(), getppid());
        sleep(15);
    }
    return 0;
}