#include<ext/pool_allocator.h>
#include<memory>
#include<iostream>
#include<unistd.h>
using namespace std;

template<typename Alloc>
void cookietest(Alloc alloc,int n)
{
    typedef typename Alloc::value_type T;
    T *p1, *p2, *p3;

    p1 = alloc.allocate(n);
    p2 = alloc.allocate(n);
    p3 = alloc.allocate(n);

    cout << "p1=" << p1 << endl
         << "p2=" << p2 << endl
         << "p3=" << p3 << endl;
    alloc.deallocate(p1, sizeof(T));
    alloc.deallocate(p2, sizeof(T));
    alloc.deallocate(p3, sizeof(T));
    cout << getpid() << endl;
    getchar();
}

// template<typename Alloc>
// void cookietest(Alloc alloc,int n)
// {
//     typedef typename Alloc::value_type T;
//     T *p1, *p2, *p3;
//     p1 = alloc.allocate(n);
//     p2 = alloc.allocate(n);
//     p3 = alloc.allocate(n);

//     printf("p1=%d\n", p1);
//     printf("p2=%d\n", p2);
//     printf("p3=%d\n", p3);

//     alloc.deallocate(p1, sizeof(T));
//     alloc.deallocate(p2, sizeof(T));
//     alloc.deallocate(p3, sizeof(T));
// }

int main()
{
    //gnu下的pool_alloc不是pool_allocator
    cookietest(__gnu_cxx::__pool_alloc<int>(), 1);
    cookietest(allocator<int>(), 1);
}