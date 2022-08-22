#include<iostream>
#include<typeinfo>
#include<vector>
#include<forward_list>
using namespace std;

template<class I>//泛化版本 接收任意类型的迭代器
struct Iter_traits
{
    typedef typename I::value_type value_type;  
    typedef typename I::iterator_category iterator_category;
};

template<class I>
struct Iter_traits<I*>//特化版本，要是个指针的话执行这个类
{
    typedef I value_type;
    typedef random_access_iterator_tag iterator_category;
};

template <typename I>
void func(I iter)
{
    /*
    typename Iter_traits<I>::value_type my_value;
    [typename XX]是一个类型，int或者double这个意思，后面在跟一个变量名
    就相当于int a这个意思
    注意着两个的差别
    typename xx a;声明一个对象
    typedef typename xx a;a是一个类型
    */
    typename Iter_traits<I>::value_type my_value;
    typename Iter_traits<I>::iterator_category my_iter_category;

    cout << typeid(my_value).name() << endl;
    cout << typeid(my_iter_category).name() << endl;
}

int main()
{
    vector<string> v1;
    int b = 1;
    int *a = &b;
    forward_list<int> list;
    func(v1.begin());
    func(a);
    func(list.begin());
}