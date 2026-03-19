#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

//Deadlock: when process p1 is holding resource r1 and waiting for resource r2.
//when process p2 is holding resource r2 but waiting for r1.
//Mutex locks should be done is same pattern, should not reverse in case of second thread.
//to avoid deadlock

int myAmount = 0;
mutex mymutex1;
mutex mymutex2;

void fun1()
{
    mymutex1.lock();
    mymutex2.lock();
    for(int i=0; i<100000; i++)
    {
		myAmount+= 10; 		
    }
	mymutex1.unlock();
	mymutex2.unlock();
    
}

void fun2()
{
    mymutex2.lock();
    mymutex1.lock();
    for(int i=0; i<100000; i++)
    {
		myAmount+= 10; 		
    }
	mymutex2.unlock();
	mymutex1.unlock();
    
}


int main()
{
    std::thread t1(fun1);
    std::thread t2(fun2);
    t1.join();
    t2.join();
    cout<<"Amount="<<myAmount<<"\n";
    return 0;
}
