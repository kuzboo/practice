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
    pthread_mutex_init(&m_lock);
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