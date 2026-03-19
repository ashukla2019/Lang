Static data members are class members that are declared using static keywords. A static member has certain special 
characteristics which are as follows:

1) Only one copy of that member is created for the entire class and is shared by all the objects of that class, 
   no matter how many objects are created.
2) It is initialized before any object of this class is created, even before the main starts.
3) It is visible only within the class, but its lifetime is the entire program.

Syntax:
static data_type data_member_name;

// C++ Program to demonstrate 
// the working of static data member
#include <iostream>
using namespace std;
 
class A {
public:
    A() 
    { 
      cout << "A's Constructor Called " << 
               endl; 
    }
};
 
class B {
    static A a;
 
public:
    B() 
    { 
      cout << "B's Constructor Called " << 
               endl; 
    }
};
 
// Driver code
int main()
{
    B b;
    return 0;
}
Output
B's Constructor Called 
Explanation: The above program calls only B’s constructor, it doesn’t call A’s constructor. The reason is,

Static members are only declared in a class declaration, not defined. They must be explicitly defined outside the class using
the scope resolution operator.

Accessing a Static Member
As told earlier, the static members are only declared in the class declaration. If we try to access the static data member without an explicit definition, the compiler will give an error. 

// C++ Program to demonstrate 
// the Compilation Error occurred
// due to violation of Static
// Data Memeber Rule
#include <iostream>
using namespace std;
 
class A {
    int x;
 
public:
    A() 
    { 
      cout << "A's constructor called " << 
               endl; 
    }
};
 
class B {
    static A a;
 
public:
    B() 
    { 
      cout << "B's constructor called " << 
               endl; 
    }
    static A getA() 
    { 
      return a; 
    }
};
 
// Driver code
int main()
{
    B b;
    A a = b.getA();
    return 0;
}
Output

Compiler Error: undefined reference to `B::a' 
Explanation: Here static member ‘a’ is accessed without explicit definition. If we add the definition, the program will work fine and call A’s constructor. 

Defining Static Data Member
To access the static data member of any class we have to define it first.

// C++ program to access static data
// member with explicit definition
#include <iostream>
using namespace std;
 
class A {
    int x;
 
public:
    A() 
    { 
      cout << "A's constructor called " << 
               endl; 
    }
};
 
class B {
    static A a;
 
public:
    B() 
    { 
      cout << "B's constructor called " << 
               endl; 
    }
    static A getA() 
    { 
      return a; 
    }
};
 
// Definition of a
A B::a; 
 
// Driver code
int main()
{
  B b1, b2, b3;
  A a = b1.getA();
 
  return 0;
}
Output
A's constructor called 
B's constructor called 
B's constructor called 
B's constructor called 
Explanation: The above program calls B’s constructor 3 times for 3 objects (b1, b2, and b3), but calls A’s constructor only once. The reason is that the static members are shared among all objects. That is why they are also known as class members or class fields. 

Also, static members can be accessed without any object.

NOTE: Static data members can only be defined globally in C++. The only exception to this are static const data members of integral type which can be initialized in the class declaration.

Access Static Members Without Any Object
We can access any static member without any object by using the scope resolution operator directly with the class name.

// C++ Program to demonstrate 
// static members can be accessed 
// without any object
#include <iostream>
using namespace std;
 
class A {
    int x;
 
public:
    A() 
    { 
      cout << "A's constructor called " << 
               endl; 
    }
};
 
class B {
    static A a;
 
public:
    B() 
    { 
      cout << "B's constructor called " << 
               endl;
    }
    static A getA() 
    { 
      return a; 
    }
};
 
// Definition of a
A B::a; 
 
// Driver code
int main()
{
  // static member 'a' is accessed 
  // without any object of B
  A a = B::getA();
 
  return 0;
}
Output
A's constructor called 
Static Data Members in Local Classes
In C++, we cannot declare static data members in local classes.

