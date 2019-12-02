#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    pid_t id;
    unsigned char cmd[128], ext[128], bin[128] = "/bin/";
    if(argc != 1) {
        printf("Command not entered\n");
        exit(1);
    }
    printf("%s\n", argv[0]);
    //cmd[128] = argv[0];
    while(1)
    {
        printf("Enter command:");
        scanf("%s",cmd);
        strcat(bin,cmd);
        //printf("Enter ext.:");
        //scanf("%s",ext);
        
        id = fork();
        if (id == -1) {
            perror("fork");
            exit(1);
        }
        if(0 == id)
        {
            //char *cmd1 = getenv(cmd);
            //printf("%s\n",cmd1);
            execl((const char*)bin,"","-al",NULL);
        }
        else
        {
            //printf("Parent\n");
        }
    }
}

    
