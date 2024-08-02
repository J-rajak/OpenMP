#include <stdio.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t mutex;

int doSomething(int threadID, int count)
{
    printf("Thread %d: Counter=%d\n", threadID, counter);
    return count + 1;
}

void *threadOne(void *p)
{
    for (int i = 0; i < 100; i++)
    {
        pthread_mutex_lock(&mutex);
        counter = doSomething(1, counter);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *threadTwo(void *p)
{
    for (int i = 0; i < 100; i++)
    {
        pthread_mutex_lock(&mutex);
        counter = doSomething(2, counter);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void main()
{
    pthread_t thrID1, thrID2;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&thrID1, NULL, threadOne, NULL);
    pthread_create(&thrID2, NULL, threadTwo, NULL);
    pthread_join(thrID1, NULL);
    pthread_join(thrID2, NULL);
    printf("Final counter = %d\n", counter);
}