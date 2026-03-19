#include <iostream>
using namespace std;

template <typename T, int size> //Template is taking argument type and not-type(size)
class stack
{
	T arr[size];
	int top;
public:
	stack():top(-1)
	{
		cout<<"Ctor"<<endl;
	}
	bool push(int data)
	{
		if(top >=size-1)
		{
			cout<<"stack overfllow"<<endl;
			return false;
		}
		else
		{
			arr[++top] = data;
			return true;
		}
	}
	T pop()
	{
		if(top <0)
		{
			cout<<"stack underflow"<<endl;
		}
		else
		{
			return arr[top--];
		}
	}
	void display()
	{
		cout<<"elements are:"<<endl;
		for(int i =0; i<=top; i++)
		{
			cout<<"elements are:"<<arr[i]<<endl;
		}
	}
};


int main() 
{
    stack<int, 5>s1;
	s1.push(10);
	s1.push(20);
	s1.push(30);
	s1.pop();
	s1.display();
    return 0;
}
