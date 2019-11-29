#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#define BUFF_SIZE 4096

int main(int argc, char *argv[])
{
    int fdr;
    char buf2[BUFF_SIZE];
    fdr = open("desdfifo", O_RDONLY);
    if(-1 == fdr)
    {
        perror("Error opening the file\n");
        exit(EXIT_FAILURE);
    }
    read(fdr, buf2, BUFF_SIZE);
    printf("Rcvd from user1: %s\n", buf2);
    close(fdr);
    fdr = open("desdfifo", O_WRONLY);
    if(-1 == fdr)
    {
        perror("Error opening the file\n");
        exit(EXIT_FAILURE);
    }
    write(fdr, "World\n", 6);
    close(fdr);
}