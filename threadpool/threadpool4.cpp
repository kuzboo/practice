#include<list>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<assert.h>
#include<iostream>
using namespace std;

template <typename T>
class threadpool
{
public:
    threadpool(int thread_nums = 8, int max_request = 1000, bool stop = false);
    ~threadpool();
    bool append(T *request);
private:
    void run();
    static void *worker(void *arg);

private:
    int m_thread_nums;
    int m_max_request;
    pthread_t *m_thread;
    list<T *> m_workqueue;
    pthread_mutex_t m_lock;
    sem_t m_task_num;
    bool m_stop;
};

template <typename T>
threadpool<T>::threadpool(int thread_nums, int max_request, bool stop)
    : m_thread_nums(thread_nums), m_max_request(max_request), m_stop(stop)
{
    pthread_mutex_init(&m_lock, NULL);
    sem_init(&m_task_num, 0,0);

    m_thread = new pthread_t[m_thread_nums];
    assert(m_thread != NULL);

    for (int i = 0; i < thread_nums; ++i)
    {
        assert(pthread_create(m_thread + i, NULL, worker, this) == 0);
        cout << "创建线程:" << i << endl;
        assert(pthread_detach(m_thread[i]) == 0);
    }

    cout << "构造函数" << endl;
}
template<typename T>
threadpool<T>::~threadpool()
{
    pthread_mutex_destroy(&m_lock);
    sem_destroy(&m_task_num);
    delete[] m_thread;
    cout << "析构函数" << endl;
}

template<typename T>
bool threadpool<T>::append(T *request)
{
    pthread_mutex_lock(&m_lock);
    if (m_workqueue.size() >= m_max_request)
    {
        cout << "工作线程队列已满" << endl;
        pthread_mutex_unlock(&m_lock);
    }
    m_workqueue.push_back(request);
    pthread_mutex_unlock(&m_lock);
    sem_post(&m_task_num);
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
    while(!m_stop)
    {
        sem_wait(&m_task_num);
        pthread_mutex_lock(&m_lock);

        if(m_workqueue.empty())
        {
            pthread_mutex_unlock(&m_lock);
            continue;
        }
        T *request = m_workqueue.front();
        m_workqueue.pop_front();

        pthread_mutex_unlock(&m_lock);

        /*具体的任务逻辑*/
    }
}

int main()
{
    threadpool<int> *pool = new threadpool<int>(8, 1000, false);
}