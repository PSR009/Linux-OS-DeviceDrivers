#include <unistd.h>
#include <fcntl.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFF_SIZE 1024
int main(int argc, char *argv[])
{
    int pfd[2];
    pid_t id;
    unsigned char buf[BUFF_SIZE];
    if (pipe(pfd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    id = fork();
    if (id == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (0 == id) { 
        close(pfd[1]); 
        read(pfd[0], buf, BUFF_SIZE);
        printf("Child rcvd from Parent: %s\n", buf);
    }
    else {
        close(pfd[0]);         
        write(pfd[1], argv[1], strlen(argv[1]));
    }
}