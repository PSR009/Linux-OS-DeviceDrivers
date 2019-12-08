#include <stdio.h>
#include <stdlib.h>
#define BUFF_SIZE 64

int main(int argc, char *argv[])
{
    FILE *src, *dst;
    size_t in, out;
    char buf[BUFF_SIZE];

    src = fopen("s2.txt", "r");
    if (NULL == src)
    {
        perror("Error opening the source file\n");
        exit(EXIT_FAILURE);
    }
    dst = fopen("d2.txt", "w");
    if (dst < 0)
    {
        perror("Error opening the dest. file\n");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        in = fread(buf, 1, BUFF_SIZE, src);
        if (0 == in)
            break;
        out = fwrite(buf, 1, in, dst);
        if (0 == out)
            break;
    }
    printf("FILES COPIED\n");
    fclose(src);
    fclose(dst);
    exit(0);
}