#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFF_SIZE 1024
char send_buff[BUFF_SIZE] = "Hello Mr.Beast!\n";
char recv_buff[BUFF_SIZE];
int s[2], r;

void add()
{
    int fd, err;
    fd = open("/dev/AddDev", O_RDWR);
    if (fd < 0)
    {
        perror("\nError: Couldn't open add device\n");
        return fd;
    }

    write(fd, &s, sizeof(s));
    printf("\nWriting to add device\n");

    err = read(fd, &r, sizeof(int));
    if (err < 0)
    {
        perror("Error: Couldn't read from add device\n");
        return err;
    }
    printf("\nReading from add device: sum = %d\n", r);
}

int main()
{
    printf("\n\n\t\t\tCalculator Driver\n\n");
    int ch;
    while (1)
    {
        printf("1 - Add\n2 - Subtract\n3 - Multiply\n4 - Divide\n5 - Exit\nYour choice:");
        scanf("%d", &ch);
        printf("\nEnter a:");
        scanf("%d", &s[0]);
        printf("\nEnter b:");
        scanf("%d", &s[1]);

        switch (ch)
        {
        case 1:
            add(n);
            break;
        case 2:
            sub(n;
            break;
        case 3:
            mul(n);
            break;
        case 4:
            div(n);
            break;
        default:
            exit(0);
        }
    }
    return 0;
}