#include<semaphore.h>

#define N 5
sem_t fork[N];

void smart_person1(int i)
{
    while (1)
    {
        /* code */
        think();
        P(fork[i]);
        P(fork[(i + 1) % 5]);
        eat();
        V(fork[i]);
        V(fork[(i + 1) % 5]);
    }
}

void smart_person2(int i)
{
    while(1)
    {
        think();
        lock();
        P(fork[i]);
        P(fork[(i + 1) % N]);
        eat();
        V(fork[i]);
        V(fork[(i + 1) % N]);
        unlock();
    }
}

void smart_person3(int i)
{
    while(1)
    {
        think();
        if (i % 2 == 0)
        {
            P(fork[i]);
            P(fork[(i + 1) % N]);
        }
        else 
        {
            P(fork[(i + 1) % N]);
            P(fork[i]);
        }
        eat();
        V(fork[i]);
        V(fork[(i + 1) % N]);
    }
}
