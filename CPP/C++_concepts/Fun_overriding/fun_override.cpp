#include <iostream>
using namespace std;

/*
Function overriding:
When it redefines a function of the base class in a derived class with the same 
signature i.e., name, return type, and parameter but with a different definition
*/

class A 
{
public:
    void fun1()
    {
        cout<<"A::fun1()\n";
    }
	void fun3()
    {
        cout<<"A::fun3()\n";
    }
   
};
class B: public A 
{
public:
    void fun1()   //Derived class is overriding functionality of Base class's fun1.
    {
        cout<<"B::fun1()\n";
    }
	void fun2()   //Derived class is overriding functionality of Base class's fun1.
    {
        cout<<"B::fun1()\n";
    }
};

int main()
{
    B b;
	b.fun1(); //will call overriding method of class B::fun1()
	A a;
	a.fun1(); //will call A::fun1()
	a.fun2(); //error: class A has no member named fun2()
	b.fun3(); //will call A::fun3() as it has derived from Base class.
    return 0;
}