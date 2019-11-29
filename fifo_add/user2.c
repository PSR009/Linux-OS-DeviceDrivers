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
    int fdr, b[2], c;
    fdr = open("desdfifo", O_RDONLY);
    if(-1 == fdr)
    {
        perror("Error opening the file\n");
        exit(EXIT_FAILURE);
    }
    read(fdr, &b, 8);
    printf("Rcvd from user1: %d, %d\n", b[0], b[1]);
    close(fdr);
    c = b[0] + b[1];
    printf("Sending sum = %d\n", c);
    fdr = open("desdfifo", O_WRONLY);
    if(-1 == fdr)
    {
        perror("Error opening the file\n");
        exit(EXIT_FAILURE);
    }
    write(fdr, &c, 4);
    close(fdr);
}