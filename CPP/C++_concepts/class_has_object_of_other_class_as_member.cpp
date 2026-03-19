#include <iostream>
#include <string>
using namespace std;
class A
{
	int x;
public:
	A(){}
	A(int x):x(x){cout<<"parametrized ctr is called\n";}
	A(const A& a){cout<<"copy ctr is called\n";}
	A& operator=(const A&)
	{
		cout<<"assignment optr is called\n";
		return *this;
	}
};
class B
{
	int* ptr;
	A a;
public:
	B(int y, A a):ptr(new int),a(a)
	{
		*ptr = y;
	}
	B(const B& b):a(b.a) //a(b.a) will call copy ctr of class A.
	{
		ptr = new int();
		*ptr = *b.ptr;
		//a = b.a; //this will call assignment operator of class A.
	}
	
};
int main()
{
	A a1(10);
	B b(20, a1);
	B b1 = b;
	//b1.print();
	return 0;
}
