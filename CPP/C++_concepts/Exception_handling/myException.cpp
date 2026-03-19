#include <iostream>
#include <exception>
using namespace std;

class myException:public exception
{
	public:
		myException(){ cout<<"my exception object is called!"<<"\n";}
		const char* what() const throw()
		{
			return "C++ exception";
		}
};

int main()
{
	try
	{
		int x = 10;
		if(x < 18)
		{
			throw myException();
		}
		else
		{
			cout<<"You are eligible";
		}
	}
	catch(myException& e)
	{
		cout<<"We have caught exception"<<e.what()<<"\n";
	}
	return 0;
}