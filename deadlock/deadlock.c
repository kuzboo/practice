#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
pthread_mutex_t lockA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lockB = PTHREAD_MUTEX_INITIALIZER;

void *threadA(void *arg)
{
    printf("Thread A waiting for lockA\n");
    pthread_mutex_lock(&lockA);
    printf("Thread A get lock A\n");

    sleep(2);

    printf("Thread A waiting for lockB\n");
    pthread_mutex_lock(&lockB);
    printf("Thread A get lock B\n");

    pthread_mutex_unlock(&lockB);
    pthread_mutex_unlock(&lockA);
}

void *threadB(void *arg)
{
    printf("Thread B waiting for lockB\n");
    pthread_mutex_lock(&lockB);
    printf("Thread B get lock B\n");

    sleep(2);

    printf("Thread B waiting for lockA\n");
    pthread_mutex_lock(&lockA);
    printf("Thread B get lock A\n");

    pthread_mutex_unlock(&lockA);
    pthread_mutex_unlock(&lockB);
}

int main()
{
    printf("%d\n", getpid());
    pthread_t aid, bid;
    pthread_create(&aid, NULL, threadA, NULL);
    pthread_create(&bid, NULL, threadB, NULL);

    pthread_join(aid, NULL);
    pthread_join(bid, NULL);
}