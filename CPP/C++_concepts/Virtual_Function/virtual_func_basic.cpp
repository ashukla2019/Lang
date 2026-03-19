#include <iostream>
using namespace std;

class Base
{
public:
    virtual void function1() { cout<<"Base::function1\n";};
    virtual void function2() { cout<<"Base::function2\n";};
};

class D1: public Base
{
public:
    virtual void function1() { cout<<"D1::function1\n";};
};

class D2: public Base
{
public:
    virtual void function2() { cout<<"D2::function2\n";};
};

int main()
{
    Base* b1 = new D1(); //virtual table of Derived class D1 will be called.
    b1->function1(); //D1::vtable[0] = D1::vf1
    b1->function2(); //Base::vtable[0] = Base::vf1(D1 class,s vtable will have 
    return 0;
}

/*understanding:
If we don't declare Base class function to virtual, compiler does the early binding, despite of 
assigning derived class object to Base class pointer. when we declare Base class function
to virtual compiler does late binding. Now compiler will insert *_VPTR to Base class 
and will be inherited by derived class. Compiler also creates one virtual table for each
class. Virtual table will be called of class, whose object is passed to Base class pointer.
*/