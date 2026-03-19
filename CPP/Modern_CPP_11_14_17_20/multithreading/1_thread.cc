Concurrency: You're cooking and answering emails by switching between the two quickly.
Parallelism: You're cooking and someone else is answering emails at the same time.

/*
//Thread creation in C++11:
In every C++ application there is one default main thread i.e. main() function. 
In C++ 11 we can create additional threads by creating objects of std::thread class.
Each of the std::thread object can be associated with a thread.
*/

/*
What std::thread accepts in constructor ?
We can attach a callback with the std::thread object, that will be executed when this new thread starts. These callbacks can be,
1.) Function Pointer
2.) Function Objects
3.) Lambda functions
4.) Non static member function
5.) Static member function

Thread objects can be created like this: std::thread thObj(<CALLBACK>);
New Thread will start just after the creation of new object and will execute the passed callback
in parallel to thread that has started it.
Moreover, any thread can wait for another to exit by calling join() function 
on that thread’s object.

*/

//this_thread: is namespace groups a set of functions that access the current thread.


//Creating a thread using Function Pointer:

#include <iostream>
#include <thread>
void thread_function()
{
    std::cout<<"Inside Thread :: ID  = "<<std::this_thread::get_id()<<std::endl;    
}
int main()  
{
    std::thread threadObj1(thread_function);
    std::thread threadObj2(thread_function);
 
    if(threadObj1.get_id() != threadObj2.get_id())
        std::cout<<"Both Threads have different IDs"<<std::endl;
 
        std::cout<<"From Main Thread :: ID of Thread 1 = "<<threadObj1.get_id()<<std::endl;    
    std::cout<<"From Main Thread :: ID of Thread 2 = "<<threadObj2.get_id()<<std::endl;    
 
    threadObj1.join();    
    threadObj2.join();    
    return 0;
}

//Creating thread using function object/functors:
#include <iostream>
#include <thread>

class MyFunctor
{
public:
    void operator()() {
        std::cout << "functor\n";
    }
};

int main()
{
    MyFunctor fnctor;
    std::thread t(fnctor);
    std::cout << "main thread\n";
    t.join();
    return 0;
}

//Creating threads using lambda function:
#include <iostream>
#include <thread>

int main()
{
    std::thread t([]()
    {
        std::cout << "thread function\n";
    }
    );
    std::cout << "main thread\n";
    t.join();     // main thread waits for t to finish
    return 0;
}

//Creating thread using Non-static member function:
#include <iostream>
#include <thread>

class MyFunc
{
public:
    void thread_fun() {
        std::cout << "Non-static member function\n";
    }
};

int main()
{
    MyFunc fnc;
    std::thread t(&MyFunc::thread_fun, &fnc);
    std::cout << "main thread\n";
    t.join();
    return 0;
}

//Creating thread using static member function:
#include <iostream>
#include <thread>

class MyFunc
{
public:
    static void thread_fun() {
        std::cout << "static member function\n";
    }
};

int main()
{
    MyFunc fnc;
    std::thread t(&MyFunc::thread_fun);
    std::cout << "main thread\n";
    t.join();
    return 0;
}

//
/*Join():
1) Once a thread is started, we wait for this thread to finish by calling join()
   function on thread object.
2) Double join will result into program termination.
3) If possible, we should check if thread is joinable before joining.

When a join() function is called on an thread object, then when this join(0 returns then that std::thread object has no associated thread with it. In case again join() function is called on such object then it will cause the program to Terminat
*/

/*Detach():
1) Detach is used to detach newly created thread from parent thread.
2) double detach will result into program termination. 
3) If we have detached thread, and main function is returning then detached thread
is suspended.

When you detach thread it means that you don't have to join() it before exiting main() . Thread library will actually wait for each such thread below-main, but you should not care about it. detach() is mainly useful when you have a task that has to be done in background, but you don't care about its execution.
*/

//Either join() or detach() should be called on thread object otherwise during 
//object's destructor, it will terminate the program.

void thread_function()
{
    std::cout << "thread function\n";
}

int main()
{
    std::thread t(&thread_function);
    std::cout << "main thread\n";
    // t.join();
    t.detach(); //t1 will freely, it's own --daemon process. once detached ,forever detached.
    return 0;
}

//Once a thread detached, we cannot force it to join with the main thread again. 
//So, the following line of the code is an error and the program will crash.
void thread_function()
{
    std::cout << "thread function\n";
}

int main()
{
    std::thread t(&thread_function);
    std::cout << "main thread\n";
    // t.join();
    t.detach();
    t.join();   // Error: can not join again, detached thread.
    return 0;
}

//We can keep the code safe from crashing by checking using joinable(). 
//Because it's not joinable, // the join() function won't be called, and the program runs without crash.
void thread_function()
{
    std::cout << "thread function\n";
}

int main()
{
    std::thread t(&thread_function);
    std::cout << "main thread\n";
    t.detach();
    if(t.joinable())  //it will not allow to join the thread but will not crash while
        t.join();     //calling join().
    return 0;
}

//Passing Parameters to a thread:
#include <iostream>
#include <thread>
#include <string>

void thread_function(std::string s)
{
    std::cout << "thread function ";
    std::cout << "message is = " << s << std::endl;
}

int main()
{
    std::string s = "Kathy Perry";
    std::thread t(&thread_function, s);
    std::cout << "main thread message = " << s << std::endl;
    t.join();
    return 0;
}

//Thread copy / move: Copying a thread won't compile:
#include <iostream>
#include <thread>

void thread_function()
{
    std::cout << "thread function\n";
}

int main()
{
    std::thread t(&thread_function);
    std::cout << "main thread\n";
    std::thread t2 = t;

    t2.join();

    return 0;
}

//But we can transfer the ownership of the thread by moving it:
#include <iostream>
#include <thread>

void thread_function()
{
    std::cout << "thread function\n";
}

int main()
{
    std::thread t(&thread_function);
    std::cout << "main thread\n";
    std::thread t2 = move(t);

    t2.join();

    return 0;
}

//How many threads: The thread library provides the suggestion for the number of threads:

int main()
{
    std::cout << "Number of threads = " 
              <<  std::thread::hardware_concurrency() << std::endl;
    return 0;
}

//after detach() execution main thread continues running
//after join() execution main thread pauses and waits until the new thread ends
