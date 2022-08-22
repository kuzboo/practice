#include<bits/stdc++.h>
using namespace std;

class A
{
public:
    A() { cout << "默认构造函数" << endl; }
    A(int a)
    {
        m_val = a;
        cout << "有参构造" << endl;
    }
    A(const A&a)
    {
        m_val = a.m_val;
        cout << "拷贝构造" << endl;
    }
private:
    int m_val;
};

class B
{
public:
private:
    A a;
    A b;
};

int main()
{
    
}