#include<bits/stl_iterator_base_types.h>
#include<vector>
#include<iterator>
#include<typeinfo>
#include<iostream>
using namespace std;

template<class I>
struct Iter_traits
{
    typedef typename I::value_type value_type;
};

template<class I>
struct Iter_traits<I*>
{
    typedef I value_type;
};

template<typename I>
void func(I iter)
{
    typedef typename Iter_traits<I>::value_type v1;
    cout << typeid(v1).name() << endl;
}

int main()
{
    vector<double> v1;
    func(v1.begin());
}