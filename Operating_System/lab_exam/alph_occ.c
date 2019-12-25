#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define COUNT 26

void *alph_recur(void *alph)
{
    FILE *fd;
    fd = fopen("/usr/share/dict/words", "r");
    if (fd == NULL)
    {
        perror("Error: Couldn't open");
        return NULL;
    }

    char c;
    int occ = 0;
    char letter = *((char *)alph);

    do
    {
        c = fgetc(fd);
        if (letter == c)
        {
            occ++;
        }
    } while (c != EOF);

    printf("%c = %d\n", letter, occ);
    //pthread_exit(NULL);
}

int main()
{
    int i;
    char l_case = 'a';
    char u_case = 'A';

    pthread_t lower_id[COUNT];
    pthread_t upper_id[COUNT];

    char lower_case[COUNT];
    char upper_case[COUNT];

    for (i = 0; i < COUNT; i++)
    {
        lower_case[i] = l_case++;
        if (pthread_create(&lower_id[i], NULL, alph_recur, (void *)&lower_case[i]) != 0)
        {
            fprintf(stderr, "Error: creating thread: %d\n", i + 1);
            return -1;
        }
        /*
        upper_case[i] = u_case++;
        if (pthread_create(&upper_id[i], NULL, alph_recur, (void *)&upper_case[i]) != 0)
        {
            fprintf(stderr, "Error: creating thread: %d\n", i + 1);
            return -1;
        }*/
    }

    for (i = 0; i < COUNT; i++)
    {
        if (pthread_join(lower_id[i], NULL) != 0)
        {
            fprintf(stderr, "Error: joining lower_case thread: %d\n", i + 1);
            return -1;
        }
        /*
        if (pthread_join(upper_id[i], NULL) != 0)
        {
            fprintf(stderr, "Error: joining upper_case thread: %d\n", i + 1);
            return -1;
        }*/
    }
    return 0;
}