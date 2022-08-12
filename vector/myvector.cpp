#include<cstdlib>
#include<cstring>
#include<iostream>

using namespace std;

template <typename T>
class myVector
{
public:
    myVector()
    {
        m_data = NULL;
        m_len = m_size = 0;
    }
    myVector(size_t len)
    {
        m_data = new T[len];
        m_len = len;
        m_size = 0;
    }
    myVector(const myVector& rhs)
    {
        if (this != &rhs)
        {
            //delete[] m_data; 赋值操作才需要
            m_data = new T[rhs.m_len];
            for (int i = 0; i < rhs.m_size;++i)
            {
                m_data[i] = rhs.m_data[i];
            }
            m_len = rhs.m_len;
            m_size = rhs.m_size;
        }
        return;
    }
    myVector<T>& operator=(const myVector<T> &rhs)
    {
        if(this->m_data!=rhs.m_data)
        {
            delete[] m_data;
            m_data = new T[rhs.m_len];
            for (int i = 0; i < rhs.m_size;++i)
            {
                m_data[i] = rhs.m_data[i];
            }
            m_len = rhs.m_len;
            m_size = rhs.m_size;
        }
        return *this;
    }
    T &operator[](size_t index)
    {
        return m_data[index];
    }

    void push_back(const T &_val)
    {
        if(m_size>=m_len)
        {
            size_t newLen = m_len == 0 ? 1 : 2 * m_len;
            T *newData = new T[newLen];
            //m_len = newLen;不能写这里？？
            memcpy(newData, m_data, m_len * sizeof(T));
            delete[] m_data;
            m_data = newData;
            m_len = newLen;
        }
        m_data[m_size++] = _val;
    }

    size_t size() { return m_size; }
    size_t capacity() { return m_len; }

private:
    T *m_data;
    size_t m_len;
    size_t m_size;
};

int main()
{
    myVector<int> v;
    myVector<int> v1;
    for (int i = 0; i < 10; ++i)
    {
        v.push_back(i);
        cout << v[i] << " ";
    }
    v1 = v;
    cout << endl;
    cout << v.size() << endl;
    cout << v.capacity() << endl;
    for (int i = 0; i < 10; ++i)
    {
        cout << v1[i] << " ";
    }
}