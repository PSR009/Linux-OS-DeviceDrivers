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
    char buff[BUFF_SIZE];
    fdr = open("desdfifo", O_RDONLY);
    if(fdr == -1)
    {
        perror("Error opening the file\n");
        exit(EXIT_FAILURE);
    }
    read(fdr, buff, BUFF_SIZE);
    printf("Rcvd: %s\n", buff);
    close(fdr);
}