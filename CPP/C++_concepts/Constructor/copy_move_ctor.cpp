#include <iostream>
using namespace std;

class A
{
	int* ptr;
public:
	A()=default;
	A(int x)
	{
		cout<<"conversion ctor\n";
		ptr=new int;
		*ptr=x;
	}
	A(const A& a)
	{
		cout<<"copy ctor\n";
		ptr=new int;
		*ptr=*(a.ptr);
	}
	A& operator=(const A& a)
	{
		cout<<"Assignment optr\n";
		ptr=new int;
		*ptr=*a.ptr;
		return *this;
	}

	A(A&& a)
	{
		cout<<"Move ctor\n";
		ptr=a.ptr;
		a.ptr=nullptr;
	}
	A& operator=(A&& a)
	{
		cout<<"Move Assignment optr\n";
		ptr=a.ptr;
		a.ptr=nullptr;
		return *this;
	}

	A operator+(A obj)
	{
		return (*ptr + *obj.ptr); //This will be calling conversion ctor: object has to be returned but returning value.
	}
	void print()
	{
		cout<<"val"<<*ptr;
	}
	
};

A fun(A a1)
{
	//A temp;
	return a1;
}
void fun_by_ref( A& a1)
{
    
}
A createA()
{

}
int main()
{
	A a1(10);
	A a2=a1; //will call copy ctor
	//A a2=fun(a1); //will call move ctor: A _temp = fun() then A a2= _temp;
	//A a2=move(a1); //will call move ctor
	A a3= a1+a2; // A _temp=a1+a2 => A a3=_temp(will call move to move temp object to A a3)
	a3.print();
	fun(createA()); //will create temporary object, so will call move ctor.
	//vector <A> vec;
    //vec.push_back(A(10));
	return 0;
}
