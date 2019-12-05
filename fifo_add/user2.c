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
    /*int g = mkfifo("/home/desd/Downloads/DESD_OS/fifo_add/desdfifo", 0600);
    if(-1 == g)
    {
        perror("Error opening mkfifo\n");
        exit(EXIT_FAILURE);
    }
    */
    fdr = open("desdfifo", O_RDONLY);
    if(-1 == fdr)
    {
        perror("Error opening before read\n");
        exit(EXIT_FAILURE);
    }
    read(fdr, &b, sizeof(b));
    printf("Rcvd from user1: %d, %d\n", b[0], b[1]);
    close(fdr);
    c = b[0] + b[1];
    printf("Sending sum = %d\n", c);
    fdr = open("desdfifo", O_WRONLY);
    if(-1 == fdr)
    {
        perror("Error opening before write\n");
        exit(EXIT_FAILURE);
    }
    write(fdr, &c, sizeof(c));
    close(fdr);
}