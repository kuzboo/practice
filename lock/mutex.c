#include<stdio.h>

//测试和置位 原子指令
int TestAndSet(int *old_ptr,int new)
{
    int old = *old_ptr;
    *old_ptr = new;
    return old;
}

typedef int queue_t;
typedef struct lock_t
{
    int flag;
    queue_t *q; //等待队列
} lock_t;

void init(lock_t *lock)
{
    lock->flag = 0;
    lock->q = NULL;
}

void lock(lock_t *lock)
{
    while (TestAndSet(&lock->flag, 1) == 1)
    {
        //保存现在运行线程TCB
        //将现在运行的线程TCB插入到阻塞队列中
        //将线程状态设置为阻塞态
        //调度程序
    }
}

void unlock(lock_t *lock)
{
    if(lock->q!=NULL)//等待队列不空
    {
        /**
         * 移除队头元素
         * 将该线程TCB插入到就绪队列
         * 设置线程状态位就绪态
         */
    }
    lock->flag = 0;
}