#include<pthread.h>
#include<stdio.h>
#include<unistd.h>

pthread_mutex_t lockA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lockB = PTHREAD_MUTEX_INITIALIZER;

void *threadA(void *arg)
{
    printf("线程A等待获取lockA\n");
    pthread_mutex_lock(&lockA);
    printf("线程A获得了lockA\n");

    sleep(2);

    printf("线程A等待获取lockB\n");
    pthread_mutex_lock(&lockB);
    printf("线程A获得了lockB\n");

    pthread_mutex_unlock(&lockB);
    pthread_mutex_unlock(&lockA);
}

void *threadB(void *arg)
{
    printf("线程B等待获取lockB\n");
    pthread_mutex_lock(&lockB);
    printf("线程B获得了lockB\n");

    sleep(2);

    printf("线程B等待获取lockA\n");
    pthread_mutex_lock(&lockA);
    printf("线程B获得了lockA\n");
    
    pthread_mutex_unlock(&lockA);
    pthread_mutex_unlock(&lockB);
}

int main()
{


    pthread_t tidA, tidB;

    pthread_create(&tidA, NULL, threadA, NULL);
    pthread_create(&tidB, NULL, threadB, NULL);

    pthread_join(tidA, NULL);
    pthread_join(tidB, NULL);

    return 0;
}