#include<memory>
#include<iostream>
using namespace std;

/*share_ptr循环引用问题*/
template<typename T>
class Node
{
public:
    Node(const T &value) : m_val(value)
    {
        cout << "Node()" << endl;
    }
    ~Node()
    {
        cout << " ~Node()" << endl;
        cout << "this:" << this << endl;
    }
    weak_ptr<Node<T>> m_pre;
    weak_ptr<Node<T>> m_next;
    T m_val;
};

void test()
{
    shared_ptr<Node<int>> sp1(new Node<int>(1));
    shared_ptr<Node<int>> sp2(new Node<int>(2));

    sp1->m_next = sp2;//sp2的引用+1
    sp2->m_pre = sp1;//sp1的引用+1

    cout << "sp1.use_count(): " << sp1.use_count() << endl;
    cout << "sp2.use_count(): " << sp2.use_count() << endl;
}

void test2()
{
    shared_ptr<int> sp1(new int(1));
    cout << sp1.use_count() << endl;
    shared_ptr<int> sp2(new int(2));
    cout << sp2.use_count() << endl;
    sp2 = sp1;
    cout << sp1.use_count() << endl;
    cout << sp2.use_count() << endl;
}

int main()
{
    test();
    cout << sizeof(weak_ptr<int>) << endl;
    cout << sizeof(shared_ptr<int>) << endl;
    cout << sizeof(unique_ptr<int>) << endl;
    
    return 0;
}