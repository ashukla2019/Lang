/*
***************Rule of Zero: 
“The Rule of Zero” basically states: You should NEVER implement a destructor, 
copy constructor, move constructor or assignment operators in your code. 
With the (very important) corollary to this: You should NEVER use a raw pointer to manage a
resource.

***************Rule of three:
The rule of three is also known as the Law of Big Three or The Big Three and 
prescribes for class that, if a class defines any of the mentioned three then 
it should probably explicitly define all three:

destructor
copy constructor
copy assignment constructor
These three are special member functions of class. If none of them is explicitly
defined by the programmer, then the compiler provides implicit versions. 
If any one of the above is explicitly defined that means implicit versions for
the other two must be improper and must be redefined.

This happens because implicitly generated constructors and assignment operators’ 
shallow copy the data members. We require deep copy when class contains pointers 
pointing to dynamically allocated resources.

The default destructors remove the unused objects. When there is no copy 
constructor defined then the destructor will run twice, once for objects that
contain the copy and second for objects from which the data members are copied. 
To avoid this, explicit definition becomes necessary.

**************Rule of Five:
Rule of five is an extension of the rule of three due to the introduction of 
move semantics in C++11. The rule of five is also applied in C++ for resource 
management. This rule potentially eliminates memory leaks and other problems 
in C++ code. The Rule of The Big Five states that if you have to write one of 
the following functions then you have to have a policy for all of them. 
If we have an Object Foo then we can have a FooManager that handles the 
resource Foo. When implementing FooManager, you'll likely all need the
following functions to be implemented:

Destructor: When this manager goes out of scope it should free all the resources 
it was managing.

Assignment operator:If you do not provide one the compiler creates a default 
assignment operator. The default assignment operation is a member-wise copy 
function and does a shallow copy and not a deep copy. This could cause problems
like memory leaks, wrong assignment.

Copy constructor:The compiler-supplied copy constructor does a member-wise copy 
of all the FooManagers attributes. This poses the same problems as the assignment
operator.

Move constructor:Copying objects can be expensive as it involves creating, 
copying and then destroying temporary objects. C++11 introduced the concept
of the r-value reference. An r-value reference can be explicitly bound to 
an r-value. An r-value is an unnamed object. A temporary object, in other words.
This r-value reference can be used in a constructor to create a reference to 
the r-value passed to it.

Move assignment operator:It is useful to only have one resource at a time. 
This resource's ownership can be transferred from one manager to another.
In such cases, you can provide a move assignment operator.
*/

//1) Type Inference(auto and decltype):
//Typeid is an operator which is used where the dynamic type of an object needs
//to be known.

/*
decltype Keyword: It inspects the declared type of an entity or the type of an
expression. ‘auto’ lets you declare a variable with a particular type whereas
decltype lets you extract the type from the variable so decltype is sort of an
operator that evaluates the type of passed expression.

decltype(fun1()) x; //// Data type of x is same as return type of fun1() 
*/

//Reference collapsing:


//Constexpr and static_assert:
constexpr int add(int x, int y){return x+y;}
static_assert(add(2,2)==4, "Not correct value")



   


	
		 
	 
