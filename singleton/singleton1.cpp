#include<pthread.h>

/*----------懒汉模式----------*/
class single
{
private:
    single(){};
    ~single(){};
    static single *m_instance;
public:
    static single *getinstance();
};
single *single::m_instance = NULL;
single *single::getinstance()
{
    if(m_instance==NULL)
    {
        m_instance = new single;
    }
    return m_instance;
}

class single2
{
private:
    single2(){};
    ~single2(){};
    static single2 *m_instance;
    static pthread_mutex_t m_lock;
public:
    static single2 *getinstance();
};
single2 *single2::m_instance = NULL;
pthread_mutex_t single2::m_lock = PTHREAD_MUTEX_INITIALIZER;

single2 *single2::getinstance()
{
    pthread_mutex_lock(&m_lock);
    if(m_instance==NULL)
    {
        m_instance = new single2;
    }
    pthread_mutex_unlock(&m_lock);
    return m_instance;

    /*************双检测*************/
    if(m_instance==NULL)
    {
        pthread_mutex_lock(&m_lock);
        if(m_instance==NULL)
        {
            m_instance = new single2;
        }
        pthread_mutex_unlock(&m_lock);
    }
    return m_instance;
}

class single3
{
private:
    single3(){};
    ~single3(){};
public:
    static single3 *getinstance();
};

single3 *single3::getinstance()
{
    //编译器保证内部静态变量的线程安全性
    static single3 instance;
    return &instance;
}

/*----------饿汉模式----------*/
//不需要加锁 程序运行时就对对象进行了初始化，以后不管哪个线程都是返回一个对象指针而已
//饿汉模式虽好，但其存在隐藏的问题，在于非静态对象（函数外的static对象）在不同编译单元中的初始化顺序是未定义的。
//如果在初始化完成之前调用 getInstance() 方法会返回一个未定义的实例。
class single4
{
private:
    single4(){};
    ~single4(){};
    static single4 *m_instance;
public:
    single4 *getinstance();
};

single4 *single4::m_instance = new single4;
single4 *single4::getinstance()
{
    return m_instance;
}