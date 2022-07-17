#include<atomic>
#include<iostream>
using namespace std;

template<typename T>
class SharePtr;

template<typename T>
class Counter
{
    friend class SharePtr<T>;

public:
    Counter() : m_refCnt(0){};
    ~Counter(){};
    Counter(const Counter &c) = delete;
    Counter &operator=(const Counter &c) = delete;
private:
    atomic_uint m_refCnt;
};

template<typename T>
class SharePtr
{
public:
    SharePtr(T *ptr = nullptr);
    SharePtr(const SharePtr &ptr);
    SharePtr<T> &operator=(const SharePtr &s);
    ~SharePtr();
    int use_count() { return m_cnt->m_refCnt; }

private:
    void release();

private:
    T *m_ptr;
    Counter<T> *m_cnt;
};

template <typename T>
SharePtr<T>::SharePtr(T *ptr) : m_ptr(ptr), m_cnt(new Counter<T>())
{
    if(ptr)
    {
        m_cnt->m_refCnt = 1;
    }
    cout << "constructor" << endl;
}

template<typename T>
SharePtr<T>::SharePtr(const SharePtr &s)
{
    m_ptr = s.m_ptr;
    s.m_cnt->m_refCnt++;
    m_cnt = s.m_cnt;
    cout << "copy constructor" << endl;
}
template<typename T>
SharePtr<T>::~SharePtr()
{
    release();
    cout << "distructor" << endl;
}

template<typename T>
void SharePtr<T>::release()
{
    m_cnt->m_refCnt--;
    if(m_cnt->m_refCnt<1)
    {
        delete m_ptr;
        m_ptr = nullptr;
    }
}

template<typename T>
SharePtr<T>& SharePtr<T>::operator=(const SharePtr &s)
{
    if(this->m_ptr!=s.m_ptr)
    {
        this->release();
        m_ptr = s.m_ptr;
        s.m_cnt->m_refCnt++;
        m_cnt = s.m_cnt;
    }
    cout << "Asign constructor" << endl;
    return *this;
}

int main()
{
    SharePtr<int> sp1(new int(1));
    SharePtr<int> sp2(new int(2));
    SharePtr<int> sp3(sp1);
    cout << "sp1.use_count(): " << sp1.use_count() << endl;
    cout << "sp2.use_count(): "<<sp2.use_count() << endl;
    sp2 = sp1;
    cout <<"sp1.use_count(): " <<sp1.use_count() << endl;
    cout << "sp2.use_count(): "<<sp2.use_count() << endl;
}