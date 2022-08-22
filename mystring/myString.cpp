#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;

class myString
{
public:
    myString(const char *cstr = 0);
    myString(const myString &str);
    myString &operator=(const myString &str);
    char *get_char() const { return m_data; }
    ~myString();

private:
    char *m_data;
};

myString::myString(const char *cstr)
{
    if(cstr)
    {
        m_data = new char[strlen(cstr) + 1];
        strcpy(m_data, cstr);
    }
    else
    {
        m_data = new char[1];
        *m_data = '\0';
    }
}

myString::~myString()
{
    delete[] m_data;
}

myString::myString(const myString &str)
{
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
}

myString& myString::operator=(const myString &str)
{
    if (this != &str)
    {
        delete[] m_data;
        m_data = new char[strlen(str.m_data) + 1];
        strcpy(m_data, str.m_data);
    }
    return *this;
}

ostream &operator<<(ostream &os, const myString &str)
{
    os << str.get_char();//const 对象不能调用非const成员函数 所以get_char声明为const
    return os;
}
int main()
{
    myString *s = new myString("mystring");
    myString p;
    p = *s;
    cout << *s << endl;
    cout << p << endl;
}