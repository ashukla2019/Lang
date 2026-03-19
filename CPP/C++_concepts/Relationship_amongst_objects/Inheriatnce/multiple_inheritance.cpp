#include<iostream>
using namespace std;

//Problem with multiple inheritance...if both base class has same function then 
//which will be called(ambiguity). It can be resolved by using scope(::)operator to 
//specify the function from which class is required..
//Incase of Diamond problem, we should use virtual keyword while inheriting
// Base class...

class A
{
private:
	int x; 
public:
	A()
	{
		cout<<"A's ctor"<<endl;
	}
	void draw()
	{
		cout<<"A::Draw()"<<endl;
	}
	void show1()
	{
		cout<<"A::show1()"<<endl;
	}
	
};

class B
{
private:
	int y;
public:
	B()
	{
		cout<<"B's ctor"<<endl;
	}
	void draw()
	{
		cout<<"B::Draw()"<<endl;
	}
	void show2()
	{
		cout<<"B::show2()"<<endl;
	}	
};

class C: public A, public B
{
public:
	C():A(),B()
	{
		cout<<"C's ctor"<<endl;
	}
};

int main()
{
	C c1;
	c1.show2();
	c1.B::draw(); //calling B class's draw method.....
	return 0;
}
