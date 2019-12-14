#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> //socketaddr_in structure
#include <arpa/inet.h> //inet_addr, htonsf
#include <netdb.h>

#define BUFF_SIZE 1024

int ss, cs;
int r, w;
unsigned char buff[BUFF_SIZE];
struct sockaddr_in saddr;
struct sockaddr_in caddr;


void err_check(int err, char *err_disp)
{
    if (-1 == err)
    {
        perror(err_disp);
        exit(EXIT_FAILURE);
    }
}

int main()
{
    cs = socket(AF_INET, SOCK_STREAM, 0);
    err_check(cs, "Error: couldn't create a socket\n");

    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("10.0.2.15");
    saddr.sin_port = htons(5678);

    ss = connect(cs, (struct sockaddr *)&saddr, sizeof(saddr));
    err_check(ss, "Error: couldn't connect\n");

    w = write(cs, "Hello, Client3 here\n", 20);
    err_check(w, "Error: couldn't write\n");

    r = read(cs, buff, 1024);
    err_check(r, "Error: couldn't read\n");
    printf("Server: %s\n", buff);
    sleep(10);
    close(ss);
    close(cs);

    return 0;
}
