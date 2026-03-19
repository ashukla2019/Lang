#include <iostream>
using namespace std;

//Static TypeCasting: It is a compile time cast.It does things like implicit conversions
//between types (such as int to float, or pointer to void*), and it can also call 
//explicit conversion functions.
//Ex 1:
int main()
{
	float f = 3.5;
	int a = f; // this is how you do in C
	int b = static_cast<int>(f);
	cout << b;
}

//Ex:2
#include <iostream>
using namespace std;
int main()
{
	int a = 10;
	char c = 'a';

	int* q = (int*)&c; // pass at compile time, may fail at run time
	int* p = static_cast<int*>(&c); //fails at compile time
	return 0;
}

//Static_cast can be performed for related class(derived and Base)
#include <iostream>
using namespace std;
class Base 
{
};
class Derived : public Base { // Inherited publicly not private/protected
};
int main()
{
	Derived d1;
	Base* b1 = (Base*)(&d1); // allowed
	Base* b2 = static_cast<Base*>(&d1); //performing upcasting which is correct.
	return 0;
}

