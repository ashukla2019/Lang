Destructor is an instance member function that is invoked automatically whenever an object is going to be destroyed. 
Meaning, a destructor is the last function that is going to be called before an object is destroyed.

1) A destructor is also a special member function like a constructor. Destructor destroys the class objects created by the constructor. 
2) Destructor has the same name as their class name preceded by a tilde (~) symbol.
3) It is not possible to define more than one destructor. 
4) The destructor is only one way to destroy the object created by the constructor. Hence destructor can-not be overloaded.
5) Destructor neither requires any argument nor returns any value.
6) It is automatically called when an object goes out of scope. 
7) Destructor release memory space occupied by the objects created by the constructor.
8) In destructor, objects are destroyed in the reverse of an object creation.

Syntax
~ <class-name>() {
    // some instructions
} 
Ex:1 - C++ program to demonstrate the execution of constructor
// and destructor

#include <iostream>
using namespace std;

class Test {
public:
	// User-Defined Constructor
	Test() { cout << "\n Constructor executed"; }

	// User-Defined Destructor
	~Test() { cout << "\nDestructor executed"; }
};
main()
{
	Test t;

	return 0;
}

Ex:2- C++ program to demonstrate the execution of constructor
// and destructor when multiple objects are created

#include <iostream>
using namespace std;
class Test {
public:
	// User-Defined Constructor
	Test() { cout << "\n Constructor executed"; }

	// User-Defined Destructor
	~Test() { cout << "\n Destructor executed"; }
};

main()
{
	// Create multiple objects of the Test class
	Test t, t1, t2, t3;
	return 0;
}

Ex:3-  C++ program to demonstrate the number of times
// constructor and destructors are called

#include <iostream>
using namespace std;
static int Count = 0;	 //It is static so that every class object has the same value 
class Test {
public:
	// User-Defined Constructor
	Test()
	{

		// Number of times constructor is called
		Count++;
		cout << "No. of Object created: " << Count
			<< endl;
	}

	// User-Defined Destructor
	~Test()
	{
		
		cout << "No. of Object destroyed: " << Count //It will print count in 
			<< endl;								 //decending order
		Count--;
		// Number of times destructor is called
	}
};

// driver code
int main()
{
	Test t, t1, t2, t3;

	return 0;
}
-----------------------------------------------------------------------------------------------------------
Properties of Destructor
1) The destructor function is automatically invoked when the objects are destroyed.
2) It cannot be declared static or const.
3) The destructor does not have arguments.
4) It has no return type not even void.
5) An object of a class with a Destructor cannot become a member of the union.
6) A destructor should be declared in the public section of the class.
7) The programmer cannot access the address of the destructor.

-------------------------------------------------------------------------------------------------------------------
When is the destructor called?
1) the function ends 
2) the program ends 
3) a block containing local variables ends 
4) a delete operator is called  

-----------------------------------------------------------------------------------------------------------------------------
How to call destructors explicitly?
object_name.~class_name()
How are destructors different from normal member functions?
Destructors have the same name as the class preceded by a tilde (~) 
Destructors don’t take any argument and don’t return anything

--------------------------------------------------------------------------------------------------------------------------------
When do we need to write a user-defined destructor?
If we do not write our own destructor in class, the compiler creates a default destructor for us. The default destructor works fine 
unless we have dynamically allocated memory or pointer in class. When a class contains a pointer to memory allocated in the class, 
we should write a destructor to release memory before the class instance is destroyed. This must be done to avoid memory leaks.

Can a destructor be virtual? 
Yes, In fact, it is always a good idea to make destructors virtual in the base class when we have a virtual function. 
See virtual destructor for more details.   
------------------------------------------------------------------------------------------------------------------------------
Virtual Destructor:
Deleting a derived class object using a pointer of base class type that has a non-virtual destructor results in undefined behavior.
To correct this situation, the base class should be defined with a virtual destructor. 
For example, the following program results in undefined behavior. 

// CPP program without virtual destructor 
// causing undefined behavior
#include <iostream>

using namespace std;

class base {
public:
	base()	 
	{ cout << "Constructing base\n"; }
	~base()
	{ cout<< "Destructing base\n"; }	 
};

class derived: public base {
public:
	derived()	 
	{ cout << "Constructing derived\n"; }
	~derived()
	{ cout << "Destructing derived\n"; }
};

int main()
{
derived *d = new derived(); 
base *b = d;
delete b;
getchar();
return 0;
}
Output
Constructing base
Constructing derived
Destructing base
-------------------------------------------------------------------------------------------------------------
Making base class destructor virtual guarantees that the object of derived class is destructed properly, i.e., both base class
and derived class destructors are called. For example,

// A program with virtual destructor
#include <iostream>

using namespace std;

class base {
public:
	base()	 
	{ cout << "Constructing base\n"; }
	virtual ~base()
	{ cout << "Destructing base\n"; }	 
};

class derived : public base {
public:
	derived()	 
	{ cout << "Constructing derived\n"; }
	~derived()
	{ cout << "Destructing derived\n"; }
};

int main()
{
derived *d = new derived(); 
base *b = d;
delete b;
getchar();
return 0;
}
Constructing base
Constructing derived
Destructing derived
Destructing base
