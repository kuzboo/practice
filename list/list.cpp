#include<iostream>
using namespace std;

/**
 * https://blog.csdn.net/weixin_49312527/article/details/124543185?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-124543185-blog-82845320.pc_relevant_multi_platform_featuressortv2dupreplace&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-124543185-blog-82845320.pc_relevant_multi_platform_featuressortv2dupreplace&utm_relevant_index=1
 * 
 */

template <class T>
class list;

//节点结构
template<typename T>
struct ListNode
{
    typedef ListNode<T> *NodePtr;
    ListNode() : _prev(nullptr), _next(nullptr), _data(T()){};//T()创建个临时变量
    ListNode(const T &val) : _prev(nullptr), _next(nullptr), _data(val){};

    NodePtr _prev;
    NodePtr _next;
    T _data;
};

//迭代器结构
template<class T>
class ListIterator
{
    friend class list<T>;
    typedef ListNode<T>* PNode;
    typedef ListIterator<T> Self;

public:
    ListIterator(PNode pNode = nullptr) : _pNode(pNode){};
    ListIterator(const Self &rhs) : _pNode(rhs._pNode){};

    T &operator*() { return _pNode->_data; }

    /** 重载->运算符
     * 
     */
    T *operator->() { return &(_pNode->_data); }

    /*前置++返回引用*/
    Self &operator++()
    {
        _pNode = _pNode->_next;
        return *this;
    }
    /*** 后置++
     * 为了区分传入一个int形参，调用的时候编译器默认传入0
     * 返回const value而不是reference，为了使(a++)++编译不通过，因为a++返回的还是a继续++还是a
    */
    const Self operator++(int)
    {
        Self temp(_pNode);
        _pNode = _pNode->_next;
        return temp;
    }
    
    Self &operator--()
    {
        _pNode = _pNode->_prev;
        return *this;
    }

    const Self operator--(int)
    {
        Self temp(_pNode);
        _pNode = _pNode->_next;
        return temp;
    }
    bool operator!=(const Self &rhs)
    {
        //return _pNode != rhs._pNode;
        return _pNode == rhs._pNode ? false : true;
    }
    bool operator==(const Self &rhs)
    {
        return _pNode == rhs._pNode;
    }

//private:
    PNode _pNode;
};

template<typename T>
class MyList
{
public:
    typedef ListIterator<T> iterator;
    typedef ListNode<T> Node;

public:
    MyList()
    {
        _pHead = new Node;
        creadHead();
    }
    MyList(int n,const T& val=T())
    {
        _pHead = new Node;
        creadHead();
        for (int i = 0; i < n; ++i)
        {
            push_back(val);
        }
    }
    MyList(const MyList &rhs)
    {
        _pHead = new Node;
        creadHead();
        iterator it = rhs.begin();
        while(it!=rhs.end())
        {
            push_back(*it);
            ++it;
        }
    }
    MyList& operator=(const MyList &rhs)
    {

    }

    ~MyList()
    {
        if(_pHead!=nullptr)
        {

        }
    }
    iterator begin() { return _pHead->_next; }
    iterator end() { return _pHead; }

    void push_back(const T &val) { insert(end(), val); }
    void push_front(const T &val) { insert(begin(), val); }
    void pop_back() { erase(--end()); }
    void pop_front() { erase(begin()); }

    void clear()
    {
        creadHead();
    }
    void swap(MyList &rhs);

    //在pos的前一个位置插入
    iterator insert(iterator pos,const T& val)
    {
        Node *temp = new Node(val);
        temp->_next = pos._pNode;
        temp->_prev = pos._pNode->_prev;
        temp->_prev->_next = temp;
        pos._pNode->_prev = temp;
        return iterator(temp);
    }

    //移除pos处的元素
    iterator erase(iterator pos)
    {
        iterator temp(pos._pNode->_next);//保存删除位置的下一个迭代器用作返回
        Node *pre_node = pos._pNode->_prev;
        Node *next_node = pos._pNode->_next;
        pre_node->_next = next_node;
        next_node->_prev = pre_node;
        delete pos._pNode;
        pos._pNode = nullptr;
        return temp;
    }

private:
    void creadHead()
    {
        _pHead->_next = _pHead;
        _pHead->_prev = _pHead;
    }

    Node *_pHead;
};

template<typename I>
void print(I iter_begin,I iter_end)
{
    for (; iter_begin != iter_end;++iter_begin)
    {
        cout << *iter_begin << " ";
    }
    cout << endl;
}

int main()
{
    MyList<int> list;
    for (int i = 0; i < 10;++i)
    {
        list.push_back(i);
    }
    print(list.begin(), list.end());
    list.erase(list.begin());
    print(list.begin(), list.end());
    list.pop_back();
    print(list.begin(), list.end());
    list.pop_front();
    print(list.begin(), list.end());
    list.push_back(11);
    list.push_front(-1);
    print(list.begin(), list.end());
}