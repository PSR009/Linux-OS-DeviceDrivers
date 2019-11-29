#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    printf("before exec\n");
    execl("/bin/ls","/bin/ls","-al",NULL);
    printf("after exec\n");
}
