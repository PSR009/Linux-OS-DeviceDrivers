#include<stdio.h> 
#include<sys/wait.h> 
#include<unistd.h> 
  
int main() 
{ 
    pid_t id;
    id = fork();
    if(0 == id)
    {
        printf("CHILD: PID: %d PPID: %d\n", getpid(), getppid());
    }
    else
    {
        printf("PARENT: PID: %d PPID: %d\n", getpid(), getppid());
        wait(NULL);
        printf("After wait: Child has terminated\n");
    }
    return 0; 
} 