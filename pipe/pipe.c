#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define BUFF_SIZE 4096

int main(int argc, char *argv[])
{
    int a[2], b[2], c, d;
    a[0] = atoi(argv[1]);
    a[1] = atoi(argv[2]);
    int p1[2],p2[2];
    int pp1 = pipe(p1);
    int pp2 = pipe(p2);
    pid_t id;
    char buf1[BUFF_SIZE], buf2[BUFF_SIZE];
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (pp1 == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (pp2 == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    id = fork();
    if (id == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
//child process    
    if (0 == id) {   
        close(p1[1]);
        read(p1[0], b, 8);
        printf("Child rcvd from Parent: %d,%d\n",b[0],b[1]);
        //close(p1[0]);
        close(p2[0]);
        c = b[0] + b[1];
        //printf("sum = %d\n", c);
        write(p2[1], &c, 4);//strlen(argv[2]));
    }
//parent process
    else {          
        close(p1[0]);         
        //write(p1[1], argv[1], strlen(argv[1]));
        write(p1[1], &a, 8);//strlen(argv[2]));
        //close(p1[1]);
        //close(p2[1]);
        read(p2[0], &d, 4);
        printf("Parent rcvd from Child: %d\n",d);
    }
}