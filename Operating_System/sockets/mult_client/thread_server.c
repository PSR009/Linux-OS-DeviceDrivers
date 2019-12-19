#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> //socketaddr_in structure
#include <arpa/inet.h>  //inet_addr, htons
#include <netdb.h>
#include <pthread.h>

#define BUFF_SIZE 1024

int ss, cs;
int *new_sock;
int b, l, r, w, pid, p_c, p_j;
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

void *conn_handler(void *sd)
{
    int cs = *(int *)sd;

    r = read(cs, buff, 1024);
    err_check(r, "Error: couldn't read\n");
    printf("Client: %s\n", buff);

    w = write(cs, "No service for you\n", 20);
    err_check(w, "Error: couldn't write\n");

    free(sd);
}

int main()
{
    ss = socket(AF_INET, SOCK_STREAM, 0);
    err_check(ss, "Error: couldn't create a socket\n");

    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("10.0.2.15");
    saddr.sin_port = htons(5678);

    b = bind(ss, (struct sockaddr *)&saddr, sizeof(saddr));
    err_check(b, "Error: couldn't bind\n");

    l = listen(ss, 0);
    err_check(l, "Error: while listening\n");

    while (1)
    {
        socklen_t csize;
        cs = accept(ss, (struct sockaddr *)&caddr, &csize);
        err_check(cs, "Error: couldn't accept\n");

        pthread_t listen;
        new_sock = malloc(1);
        *new_sock = cs;

        p_c = pthread_create(&listen, NULL, conn_handler, (void *)new_sock);
        err_check(p_c, "Error: Couldn't create a thread\n");

        p_j = pthread_join(listen, NULL);
        err_check(p_j, "Error: Couldn't join the thread\n");

        close(cs);
    }
    close(ss);
    return 0;
}
