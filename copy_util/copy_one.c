#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    char buf;
    int source, dest, in, out;
    if(argc!=3)
    {
        write(STDOUT_FILENO,"prgm1 s2.txt d2.txt\n",50);   
        exit(1);
    }
    source = open(argv[1],O_RDWR | O_CREAT, S_IRWXU);
    if (source == -1)
    {
        perror("SOURCE FILE ERROR");
        exit(0);
    }
    //write (source, "Hello\n", 6);
    dest = open(argv[2],O_WRONLY | O_CREAT, S_IRWXU);
    if(dest == -1)
    {
        perror("DESTINATION FILE ERROR");
        exit(0);
    }
    while((in = read (source,&buf,1)) > 0)
    {
        out = write(dest, &buf, 1);
    }
    write(STDOUT_FILENO, "FILES COPIED\n" , 15);    
    close(source);
    close(dest);
    return 0;
}