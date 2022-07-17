#include<bits/allocator.h>
#include<iostream>
using namespace std;

template <class T, class Alloc = allocator<T>>
class MyVector
{
public:
    typedef T value_type;
    typedef value_type *iterator;
    typedef value_type &reference;
    typedef size_t size_type;
private:
    iterator start;
    iterator finish;
    iterator end_of_storage;
public:
    MyVector() : start(0), finish(0), end_of_storage(0) {};
    MyVector(const size_type &n, value_type val)
    {
        start = new T(n);
        finish = n;
        for (; start < finish;++start)
            *start = val;
    }
    ~MyVector(){};
    iterator begin() { return start; }
    iterator end() { return finish; }
    size_type size() { return size_type(end() - begin()); }
    size_type capacity() { return size_type(end_of_storage - begin()); }
    bool empty() { return begin() == end(); }
    reference operator[](size_type n) { return *(begin() + n); }
private:
};

class A
{
    virtual ~A();
};

class B :public A
{
};

int main()
{
    MyVector<int> vec;
    cout << vec.size() << endl;
    MyVector<int> *vec = new MyVector<int>(10, 1);
}