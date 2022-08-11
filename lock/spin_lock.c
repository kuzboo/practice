//原子操作指令 测试和置位
int TestAndSet(int *old_ptr,int new)
{
    int old = *old_ptr;
    *old_ptr = new;
    return old;
}

typedef struct lock_t
{
    int flag;
} lock_t;

void init(lock_t *lock)
{
    lock->flag = 0;
}

void lock(lock_t *lock)
{
    //1代表锁已经被使用了,所以没有获取锁会忙等待
    while(TestAndSet(lock->flag,1)==1)
    {

    }
}

void unlock(lock_t *lock)
{
    lock->flag = 0;
}