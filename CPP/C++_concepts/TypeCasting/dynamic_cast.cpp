//Dynamic cast:A cast is an operator that converts data from one type to another type.
//dynamic casting is mainly used for safe downcasting at run time. 
//To work on dynamic_cast there must be one virtual function in the base class. 
//A dynamic_cast works only polymorphic base class because it uses this information 
//to decide safe downcasting.

//Case 1: Let’s take an example of dynamic_cast which demonstrates if the casting 
//is successful, it returns a value of type new_type.
// C++ Program demonstrates successful
// dynamic casting and it returns a
// value of type new_type
#include <iostream>

using namespace std;
// Base Class declaration
class Base {
	virtual void print()
	{
		cout << "Base" << endl;
	}
};

// Derived1 class declaration
class Derived1 : public Base {
	void print()
	{
		cout << "Derived1" << endl;
	}
};

// Derived2 class declaration
class Derived2 : public Base {
	void print()
	{
		cout << "Derived2" << endl;
	}
};

// Driver Code
int main()
{
	Derived1 d1;

	// Base class pointer holding
	// Derived1 Class object
	Base* bp = dynamic_cast<Base*>(&d1);

	// Dynamic_casting
	Derived1* dp2 = dynamic_cast<Derived1*>(bp); //Valid: Because Base class pointer holds the object of Derived class1.
	if (dp2 == nullptr)
		cout << "null" << endl;
	else
		cout << "not null" << endl;

	return 0;
}
o/p: not null

//Case 2:  Now, If the cast fails and new_type is a pointer type, 
//it returns a null pointer of that type.

#include <iostream>
using namespace std;

// Base class declaration
class Base {
	virtual void print()
	{
		cout << "Base" << endl;
	}
};

// Derived1 class declaration
class Derived1 : public Base {
	void print()
	{
		cout << "Derived1" << endl;
	}
};

// Derived2 class declaration
class Derived2 : public Base {
	void print()
	{
		cout << "Derived2" << endl;
	}
};

// Driver Code
int main()
{
	Derived1 d1;
	Base* bp = dynamic_cast<Base*>(&d1);

	// Dynamic Casting
	Derived2* dp2 = dynamic_cast<Derived2*>(bp); //not valid: converting base class pointer to
	if (dp2 == nullptr) //Derived class Derived2 but base class pointer holds object of Derived1 not Derived2.
		cout << "null" << endl;

	return 0;
}
o/p: null
