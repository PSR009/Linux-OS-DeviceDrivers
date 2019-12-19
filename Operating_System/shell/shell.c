#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFF_LEN 1024

int main()
{
    char in_line[BUFF_LEN];
    char *argv[100];
    char *path = "/bin/";
    char final_path[20];
    int argc;

    while (1)
    {
        printf(">> ");

        if (!fgets(in_line, BUFF_LEN, stdin))
        {
            break;
        }
        size_t len = strlen(in_line);
        if (in_line[len - 1] == '\n')
        {
            in_line[len - 1] = '\0';
        }
        if (strcmp(in_line, "exit") == 0)
        {
            break;
        }

        char *token;
        token = strtok(in_line, " ");
        int i = 0;
        while (token != NULL)
        {
            argv[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        argv[i] = NULL;

        argc = i;
        for (i = 0; i < argc; i++)
        {
            printf("%d: %s\n", i, argv[i]);
        }
        strcpy(final_path, path);
        strcat(final_path, argv[0]);

        for (i = 0; i < strlen(final_path); i++)
        {
            if (final_path[i] == '\n')
            {
                final_path[i] = '\0';
            }
        }
        int pid = fork();

        if (pid == 0)
        {
            execvp(final_path, argv);
            fprintf(stderr, "Child process could not do execvp\n");
        }
        else
        {
            wait(NULL);
            printf("\nChild Terminated\n\n");
        }
    }
}