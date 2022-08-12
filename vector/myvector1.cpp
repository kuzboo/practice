#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;

template <typename T>
class MyVector
{
public:
    MyVector() : m_data(NULL), m_len(0), m_size(0){};
    MyVector(size_t len)
    {
        m_data = new T[len];
        m_len = len;
        m_size = len;
    }
    MyVector(size_t len, T &&val)
    {
        m_data = new T[len];
        for (int i = 0; i < len;++i)
        {
            //*m_data = val;
            m_data[i] = val;
        }
        m_len = len;
        m_size = len;
    }
    MyVector(const MyVector &rhs)
    {
        //if(rhs.m_data!=m_data)
        if (this->m_data != &rhs.m_data)
        {
            m_data = new T[rhs.m_len];
            for (int i = 0; i < rhs.m_size;++i)
            {
                m_data[i] = rhs.m_data[i];
            }
            m_len = rhs.m_len;
            m_size = rhs.m_size;
        }
    }
    MyVector &operator=(const MyVector &rhs)
    {
        if (rhs.m_data != this->m_data)
        {
            delete[] m_data;
            m_data = new T[rhs.m_len];
            for (int i = 0;i<rhs.m_size;++i)
            {
                m_data[i] = rhs.m_data[i];
            }
            m_len = rhs.m_len;
            m_size = rhs.m_size;
        }
        return *this;
    }
    ~MyVector()
    {
        delete[] m_data;
        m_len = 0;
        m_size = 0;
        cout << "析构函数" << endl;
    }

    T &operator[](size_t index) const { return m_data[index]; }

    void push_back(const T &val)
    {
        if(m_size>=m_len)
        {
            size_t newLen = m_len == 0 ? 1 : 2 * m_len;
            T *newdata = new T[newLen];
            memcpy(newdata, m_data, m_size * sizeof(T));
            delete[] m_data;
            m_data = newdata;///这句不能少
            m_len = newLen;
        }
        m_data[m_size++] = val;
    }
    size_t size() const { return m_size; }
    size_t capacity() const { return m_len; }

private:

    size_t m_size;
    size_t m_len;
    T *m_data;
};

template<typename T>
void printVector(const MyVector<T> &vec)
{
    for (int i = 0; i < vec.size();++i)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
    cout << "size=" << vec.size() << endl;
    cout << "capacity=" << vec.capacity() << endl;
}

int main()
{
    MyVector<int> v;
    MyVector<int> v1;
    MyVector<int> v2(10, 2);
    for (int i = 0; i < 10; ++i)
    {
        v.push_back(i);
    }
    printVector(v);
    v1 = v;
    printVector(v1);
    printVector(v2);
}