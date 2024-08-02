
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <omp.h>

char *messages[3] = {NULL, NULL, NULL};
omp_lock_t lock;

void messenger()
{
    int tid = omp_get_thread_num();
    char tmpbuf[100];

    for (int i = 0; i < 10; i++)
    {
        /* Sending a message */
        int dest = (tid + 1) % 3;

        omp_set_lock(&lock);

        sprintf(tmpbuf, "Hello from Thread %d!", tid);
        char *msg = strdup(tmpbuf);
        messages[dest] = msg;
        printf("Thread %d sent the message to Thread %d\n", tid, dest);
        /* Receiving a message */
        printf("Thread %d received the message '%s'\n", dest, messages[dest]);

        omp_unset_lock(&lock);

        free(messages[dest]);
        messages[dest] = NULL;
    }
}

void main()
{
    omp_init_lock(&lock);

#pragma omp parallel num_threads(10)
    messenger();

    omp_destroy_lock(&lock);
}