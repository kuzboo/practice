#include<iostream>
#include<deque>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<unistd.h>
using namespace std;

deque<int> q;
mutex mt;
condition_variable cond;

void producer()
{
    int count = 10;
    while(count>0)
    {
        unique_lock<mutex> unique(mt);
        q.push_front(count);
        unique.unlock();
        cout << "Producer a value" << count << endl;
        cond.notify_one();
        count--;
        sleep(1);
    }
}
void consumer()
{
    int data = 0;
    while(data!=1)
    {
        unique_lock<mutex> unique(mt);
        while(q.empty())
        {
            cond.wait(unique);
        }
        data = q.back();
        q.pop_back();
        cout << "consumer a value" <<data << endl;
        unique.unlock();
    }
}

int main()
{
    thread t1(consumer);
    thread t2(producer);
    t1.join();
    t2.join();
    return 0;
}