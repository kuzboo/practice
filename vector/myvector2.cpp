#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;

template<typename T>
class MyVector
{
public:
    typedef T *itreator;

    MyVector() : _val(nullptr), _size(0), _len(0){}
    MyVector(size_t size, const T &val);
    MyVector(const MyVector &rhs);
    ~MyVector() {
        delete[] _val;
        _size = 0;
        _len = 0;
    }

    MyVector &operator=(const MyVector &rhs);
    T &operator[](const int index) const { return _val[index]; }
    void push_back(const T &val);
    void pop_back();
    size_t size() const { return _size; }
    size_t capacity() const { return _len; }
    T *begin() const { return _val; }
    //T *end() const { return _val + _size*sizeof(T); }
    T *end() const { return _val + _size; }

private:
    T *_val;
    size_t _size;
    size_t _len;
};

template<typename T>
MyVector<T>::MyVector(size_t size, const T &val)
{
    _val = new T[size];
    for (int i = 0; i < size; ++i)
    {
        _val[i] = val;
    }
    _size = size;
    _len = size;
}

template<typename T>
MyVector<T>::MyVector(const MyVector &rhs)
{
    if(_val!=rhs._val)
    {
        _size = rhs._size;
        _len = rhs._len;
        _val = new T[_len];
        memcpy(_val, rhs._val, _size * sizeof(T));
    }
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector&rhs)
{
    if(_val!=rhs._val)
    {
        delete[] _val;
        _size = rhs._size;
        _len = rhs._len;
        _val = new T[_len];
        memcpy(_val, rhs._val, _size * sizeof(T));
    }
    return *this;
}

template <typename T>
void MyVector<T>::push_back(const T &val)
{
    if (_size == _len)
    {
        size_t new_len = _len == 0 ? 1 : 2 * _len;
        T *new_val = new T[new_len];
        memcpy(new_val, _val, _size * sizeof(T));
        delete[] _val;
        _val = new_val;
        _len = new_len;
    }
    _val[_size++] = val;
}

template <typename T>
void MyVector<T>::pop_back()
{
    if (_size != 0)
    {
        _val[_size--] = T();
    }
}

template<typename T>
ostream &operator<<(ostream &os, const MyVector<T> &vec)
{
    for (int i = 0; i < vec.size();++i)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
    cout << "size:" << vec.size() << endl;
    cout << "capacity:" << vec.capacity() << endl;
}

int main()
{
    MyVector<int> v1(10, 1);
    MyVector<int> v2;
    MyVector<int> v3;
    v2.push_back(1);
    for (int i = 0; i < 10;++i)
    {
        v3.push_back(i);
    }
    cout << v1;
    cout << v2;
    cout << v3;
    MyVector<int> v4 = v3;
    cout << "*it:" << *(v3.begin()) << endl;
    v3.pop_back();
    cout << v3;
    for (auto it = v4.begin(); it != v4.end();++it)
    {
        cout << *it << " ";
    }
    cout << endl;
}