#include<atomic>
#include<iostream>
#include<vector>
using namespace std;
template <typename T>
class SharePtr;
template <typename T>
class Counter
{
    friend class SharePtr<T>;//这里要带模板参数
public:
    Counter() : m_refCount(0){};
    ~Counter(){};
private:
    atomic_uint m_refCount;//原子操作
};

template<typename T>
class SharePtr
{
public:
    SharePtr(T *ptr);
    ~SharePtr();
    SharePtr(const SharePtr &s);
    SharePtr<T> &operator=(const SharePtr &s);  //因为要返回具体的类型所以要加模板参数
    T &operator*() { return *m_ptr; }
    T *operator->() { return m_ptr; }
    int use_count() { return m_cnt->m_refCount; }
private:
    void release();
private:
    T *m_ptr;
    Counter<T> *m_cnt;
};
template<typename T>
SharePtr<T>::SharePtr(T *ptr):m_ptr(ptr),m_cnt(new Counter<T>)
{
    if(ptr)
    {
        m_cnt->m_refCount = 1;
    }
    cout << "Constructor " << endl;
}
template<typename T>
SharePtr<T>::~SharePtr()
{
    release();
    cout << "distructor" << endl;
}
template <typename T>
SharePtr<T>::SharePtr(const SharePtr &s)
{
    m_ptr = s.m_ptr;
    s.m_cnt->m_refCount++;
    m_cnt = s.m_cnt;
    cout << "Copy Constructor " << endl;
}
template <typename T>
SharePtr<T> &SharePtr<T>::operator=(const SharePtr &s)
{
    if(this->m_ptr != s.m_ptr)
    {
        this->release();  //本来的对象引用计数要--
        m_ptr = s.m_ptr;
        s.m_cnt->m_refCount++;
        m_cnt = s.m_cnt;
        cout << "Assign Constructor" << endl;
    }
    return *this;
}
template<typename T>
void SharePtr<T>::release()
{
    m_cnt->m_refCount--;
    if(m_cnt->m_refCount<1)
    {
        delete m_ptr;
        m_ptr = nullptr;
    }
}

int main()
{
    SharePtr<int> sp1(new int(1));
    SharePtr<int> sp2(new int(2));
    SharePtr<int> sp3(sp2);
    cout << "sp1.use_count(): " << sp1.use_count() << endl;
    cout << "sp2.use_count(): "<<sp2.use_count() << endl;
    sp2 = sp1;

    cout <<"sp1.use_count(): " <<sp1.use_count() << endl;
    cout << "sp2.use_count(): "<<sp2.use_count() << endl;
}