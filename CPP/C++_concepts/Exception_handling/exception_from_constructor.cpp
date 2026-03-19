//Example for constructor throws an exception and catch is present in main.
#include <iostream>

class A
{
	private:
		int a;
	public:
	A() 
	{ 
		a = 7; 
		throw 42; 
	}
	int getA() 
	{ 
		return a; 
	}
};

int main (void) 
{
	A *ptr;
	try 
	{
		ptr = new A();
	} 
	catch (int b)
	{
		std::cout << "Exception: " << b <<"\n";
		return -1;
	}
	std::cout << "Value: " << ptr ->getA() <<"\n";
	return 0;
}