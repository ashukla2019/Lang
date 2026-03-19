#include iostream
#include cstring
using namespace std;

/* Friend function

class A
{
	int x;
	public: 
		A(int x):x(x){}
		friend void fun(A& a1);
};

void fun(A& a1)
{
	cout<<a1.x;
}

int main()
{
	A a1(10);
	fun(a1);
	return 0;
}
*/

//friend class
class A
{
	int x;
	public 
		A(int x)x(x){}
		friend class B;
};

class B
{
	int y;
	public 
		B(int x)y(x){}
		void fun(A& a1)
		{
			couta1=a1.x;
		}
};

int main()
{
	A a1(10);
	B b1(10);
	b1.fun(a1);
	return 0;
}