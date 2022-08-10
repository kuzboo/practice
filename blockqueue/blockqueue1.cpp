/*基于阻塞队列的生产者消费者进程*/
#include<iostream>
#include<list>
#include<pthread.h>
#include<unistd.h>

using namespace std;

template<typename T>
class BlockQueue
{
public:
    BlockQueue(int max_requests);
    ~BlockQueue();
    bool push(const T &val);
    bool pop(T &val);

private:
    list<T > m_queue;
    pthread_mutex_t m_lock;
    pthread_cond_t m_cond;
    int m_max_requests;
};

template<typename T>
BlockQueue<T>::BlockQueue(int max_requests):m_max_requests(max_requests)
{
    pthread_mutex_init(&m_lock, NULL);
    pthread_cond_init(&m_cond, NULL);
}

template<typename T>
BlockQueue<T>::~BlockQueue()
{
    pthread_mutex_destroy(&m_lock);
    pthread_cond_destroy(&m_cond);
}

template<typename T>
bool BlockQueue<T>::push(const T &val)
{
    pthread_mutex_lock(&m_lock);
    if(m_queue.size()>=m_max_requests)
    {
        cout << "队列满了" << endl;
        pthread_cond_broadcast(&m_cond);
        pthread_mutex_unlock(&m_lock);
        return false;
    }
    
    m_queue.push_back(val);
    pthread_cond_broadcast(&m_cond);
    pthread_mutex_unlock(&m_lock);
    return true;
}

template<typename T>
bool BlockQueue<T>::pop(T &val)
{
    
    /*再具体点，有可能多个线程都在等待这个资源可用的信号，
    信号发出后只有一个资源可用，但是有A，B两个线程都在等待，
    B比较速度快，获得互斥锁，然后加锁，消耗资源，然后解锁，
    之后A获得互斥锁，但A回去发现资源已经被使用了，它便有两个选择，
    一个是去访问不存在的资源，另一个就是继续等待，
    那么继续等待下去的条件就是使用while，要不然使用if的话pthread_cond_wait返回后，
    就会顺序执行下去。*/
    pthread_mutex_lock(&m_lock);
    //多个消费者用while
    while(m_queue.empty())
    {
        //返回0表示抢到互斥锁
        if(pthread_cond_wait(&m_cond,&m_lock)!=0)
        {
            pthread_mutex_unlock(&m_lock);
            return false;
        }
    }
    val = m_queue.front();
    m_queue.pop_front();
    pthread_mutex_unlock(&m_lock);
    return true;
}


void *producer(void *arg)
{
    BlockQueue<int> *workqueue = (BlockQueue<int> *)arg;
        int data = rand() % 100 + 1;
        workqueue->push(data);
        cout << "生产了一个数据" << data << endl;
        sleep(1);
}

void *consumer(void *arg)
{
    BlockQueue<int> *workqueue = (BlockQueue<int> *)arg;
        int ret;
        workqueue->pop(ret);
        cout << "消费了个" << ret << endl;
        sleep(1);
}

int main()
{
    srand(time(NULL));
    pthread_t *thread = new pthread_t[10];
    BlockQueue<int> *workqueue = new BlockQueue<int>(10);
    for (int i = 0; i < 10; ++i)
    {
        if(i%2==1)
            pthread_create(thread + i, NULL, producer, workqueue);
        else
            pthread_create(thread + i, NULL, consumer, workqueue);
        cout << "创建线程" << i << endl;
        sleep(3);
        pthread_detach(thread[i]);
    }
}