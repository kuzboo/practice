#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
typedef struct msg
{
    int val;
    struct msg *next;
} msg;
msg *head;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *producer(void *arg)
{
    while(1)
    {
        msg *p = malloc(sizeof(msg));
        p->val = rand() % 1000 + 1;
        printf("Producer:%x-----%d\n", pthread_self(), p->val);

        pthread_mutex_lock(&mutex);
        p->next = head;
        head = p;
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);

        sleep(rand() % 5);
    }
}

void *consumer(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        while(head==NULL)
        {
            pthread_cond_wait(&cond, &mutex);
        }
        msg *p = head;
        head = head->next;
        pthread_mutex_unlock(&mutex);

        printf("Consumer:%x-----%d\n", pthread_self(), p->val);
        free(p);
        sleep(rand() % 5);
    }
}

int main()
{
    pthread_t pid, cid;

    srand(time(NULL));

    pthread_create(&pid, NULL, producer, NULL);
    pthread_create(&cid, NULL, consumer, NULL);

    pthread_join(pid, NULL);
    pthread_join(cid, NULL);

    return 0;
}