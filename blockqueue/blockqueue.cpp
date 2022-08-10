#include<deque>
#include<pthread.h>

using namespace std;

template<typename T>
class BlockQueue
{
public:
    BlockQueue(int max_request);
    ~BlockQueue();
    bool push(T &val);
    bool pop(T &val);

private:
    int m_max_requests;
    deque<T *> m_workqueue;
    pthread_mutex_t m_lock;
    //sem_t m_sem;
    pthread_cond_t m_cond;
};

template <typename T>
BlockQueue<T>::BlockQueue(int max_request) : m_max_requests(max_request)
{
    pthread_mutex_init(&m_lock,NULL);
    pthread_cond_init(&m_cond, NULL);
}
template<typename T>
BlockQueue<T>::~BlockQueue()
{
    pthread_mutex_destroy(&m_lock);
    sem_destroy(&m_sem);
}

template <typename T>
bool BlockQueue<T>::pop(T &val)
{
    pthread_mutex_lock(&m_lock);
    // if(m_workqueue.empty())
    // {
    //     pthread_mutex_unlock(&m_lock);
    //     return false;
    // }
    //多个消费者的时候，这里要是用while而不是if

    /*再具体点，有可能多个线程都在等待这个资源可用的信号，
    信号发出后只有一个资源可用，但是有A，B两个线程都在等待，
    B比较速度快，获得互斥锁，然后加锁，消耗资源，然后解锁，
    之后A获得互斥锁，但A回去发现资源已经被使用了，它便有两个选择，
    一个是去访问不存在的资源，另一个就是继续等待，
    那么继续等待下去的条件就是使用while，要不然使用if的话pthread_cond_wait返回后，
    就会顺序执行下去。*/

    while(m_workqueue.size()<=0)
    {
        pthread_cond_wait(&m_cond, &m_lock);
    }

    val = m_workqueue.front();
    m_workqueue.pop_front();
    pthread_mutex_unlock(&m_lock);
    return true;
}
template<typename T>
bool BlockQueue<T>::push(T &val)
{
    pthread_mutex_lock(&m_lock);
    if(m_workqueue.size()>=m_max_requests)
    {
        pthread_cond_broadcast(&m_cond);
        pthread_mutex_unlock(&m_lock);
        return false;
    }
    m_workqueue.push_front(val);
    pthread_cond_broadcast();
    pthread_mutex_unlock(&m_lock);
    return true;
}

