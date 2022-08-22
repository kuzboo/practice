#include<ext//pool_allocator.h>
#include<memory>
#include<iostream>
using namespace std;

template<typename Alloc>
void cookietest(Alloc alloc,int n)
{
    //typedef typename alloc::value_type T;
    typedef typename Alloc::value_type T;
    // T *p1, *p2, *p3;
    // p1 = alloc.allocate(n);
    // p2 = alloc.allocate(n);
    // p3 = alloc.allocate(n);

    // cout << "p1=" << p1 << endl
    //      << "p2=" << p2 << endl
    //      << "p3=" << p3 << endl;

    for (int i = 0; i <20;++i)
    {
        T *p = alloc.allocate(n);
        cout << "p" << i << "=" << p << endl;
    }
    // alloc.deallocate(p1, sizeof(T));
    // alloc.deallocate(p2, sizeof(T));
    // alloc.deallocate(p3, sizeof(T));
}

struct foo
{
    int a;
    int b;
    int c;
};

int
main()
{
    cookietest(__gnu_cxx::__pool_alloc<int>(), 1);
    cookietest(__gnu_cxx::__pool_alloc<foo>(), 1);
    //cookietest(allocator<int>(), 1);
    cout << sizeof(char*) << endl;
    cout << sizeof(unsigned long) << endl;
    //
    typedef unsigned int uint32
}