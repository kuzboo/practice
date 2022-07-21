#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include<list>
using namespace std;

template<typename T>
class threadpool
{
public:
    threadpool(int thread_num, int max_request);
    ~threadpool();
    bool append(T* request);

private:
    static void *worker(void *arg);
    void run();

private:
    int m_thread_num;
    int m_max_request;
    pthread_t *m_thread;
    pthread_mutex_t mutex;
    sem_t m_task_nums;
    list<T*> m_workqueue;
};

template <typename T>
threadpool<T>::threadpool(int thread_num, int max_request)
    : m_thread_num(thread_num), m_max_request(max_request)
{
    pthread_mutex_init(&mutex, NULL);
    sem_init(&m_task_nums, 0, 0);
    if(thread_num<=0 || max_request <=0)
    {

    }
    m_thread = new pthread_t(thread_num);
    for (int i = 0; i < thread_num; ++i)
    {
        if(pthread_create(m_thread+i,NULL,worker,this)!=0)
        {
            delete[] m_thread;
        }
        if(pthread_detach(m_thread[i])!=0)
        {
            delete[] m_thread;
        }
    }
}

template<typename T>
threadpool<T>::~threadpool()
{
    delete[] m_thread;
    pthread_mutex_destroy(&mutex);
    sem_destroy(&m_task_nums);
}

template<typename T>
bool threadpool<T>::append(T *request)
{
    pthread_mutex_lock(&mutex);
    if(m_workqueue.size()>=m_max_request)
    {
        return false;
    }
    m_workqueue.push_back(request);
    pthread_mutex_unlock(&mutex);
    sem_post(&m_task_nums);
    return true;
}

template<typename T>
void *threadpool<T>::worker(void *arg)
{
    threadpool *pool = (threadpool *)arg;
    pool->run();
    return pool;
}

template<typename T>
void threadpool<T>::run()
{
    while(1)
    {
        sem_wait(&m_task_nums);
        pthread_mutex_lock(&mutex);
        if(m_workqueue.empty())
        {
            continue;
        }
        T *request = m_workqueue.front();
        m_workqueue.pop_front();
        pthread_mutex_unlock(&mutex);

        //具体的任务逻辑
    }
}