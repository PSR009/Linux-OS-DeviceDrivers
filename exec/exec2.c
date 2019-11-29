#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    pid_t id;
    unsigned char cmd[128];
    while(1)
    {
        printf("Enter command:");
        scanf("%s",cmd);
        id = fork();
        if(0 == id)
        {
            execl((const char*)cmd,(const char*)cmd,NULL);
        }
    }
}

    
