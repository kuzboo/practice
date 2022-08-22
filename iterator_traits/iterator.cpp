//#include<bits/stl_iterator_base_types.h>
#include<vector>
//#include<iterator>
#include<typeinfo>
#include<iostream>
#include<forward_list>
using namespace std;

template<class I>
struct Iter_traits
{
    typedef typename I::value_type value_type;
    typedef typename I::iterator_category iterator_category;
};

template<class I>
struct Iter_traits<I*>
{
    typedef I value_type;
    typedef random_access_iterator_tag iterator_category;
};

template<typename I>
void func(I iter)
{
    typename Iter_traits<I>::value_type v1;
    typename Iter_traits<I>::iterator_category cagy;
    cout << typeid(v1).name() << endl;
    cout << typeid(cagy).name() << endl;
}

int main()
{
    vector<double> v1;
    int *a = nullptr;
    forward_list<int> list;
    func(v1.begin());
    func(a);
    func(list.begin());
}