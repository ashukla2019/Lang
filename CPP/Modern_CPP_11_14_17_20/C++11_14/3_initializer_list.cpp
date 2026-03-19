//If we create object of class, constructor is called
class A 
{
public:
	A() //first memory will be allocated to object and then data member is initialized with
	    //default value zero and then value 10 is assigned.
	{
		x = 10;
	}
	
	//if we use initializer list, first memory will be allocated to object and actual value is assigned.
};
------------------------------------------------------------------------------
1. Member Initialization in Constructors
	class MyClass {
    	int x;
    	double y;
	public:
    	MyClass(int a, double b) : x(a), y(b) {}  // initializer list
	};
---------------------------------------------------------------------------
2. std::initializer_list<T> Constructor
		
	#include <initializer_list>
	#include <iostream>
	
	class MyList {
	public:
	    MyList(std::initializer_list<int> values) {
	        for (int v : values)
	            std::cout << v << " ";
	    }
	};
	
	MyList ml = {1, 2, 3, 4};  // initializer_list constructor is called
----------------------------------------------------------------
3. Initializing STL Containers
	#include <vector>
	std::vector<int> vec = {1, 2, 3, 4};  // C++11 uniform initialization
	Uniform initialization of std::vector, std::set, etc.
-------------------------------------------------------------
 4. Function Parameters with std::initializer_list
	void printAll(std::initializer_list<int> list) {
    	for (int v : list)
        std::cout << v << " ";
	}
	printAll({10, 20, 30});
-------------------------------------------------------------------
5. Aggregate Initialization (Plain Structs)
	struct Point {
    	int x, y;
	};
	Point p = {3, 4};  // aggregate initialization
----------------------------------------------------------------------
6. Constructor Delegation Using Initializer List
	class MyClass {
    	int a, b;
	public:
    	MyClass(int x) : MyClass(x, 0) {}       // delegate to another constructor
    	MyClass(int x, int y) : a(x), b(y) {}
	};
--------------------------------------------------------------------------------------------------
7) 7. Default Member Initializers (In-Class)
	class MyClass {
    	int x = 10;
    	std::string name = "default";
	};
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------
Use of initializer list: It is used when:
	1)	To initialize reference variable
	2)	To initialize const variable
	3)	When object of one class is created in other class (required, otherwise default constructor of that class is called and if that is not implemented then there will be an error). 
		Ex: 
		class A 
		{ 
			int i,j; 
		public: 
			A(int, int ); 
		}; 
	
		A::A(int arg1, int arg2) { 
			i = arg1; 
			j = arg2;
			cout << "A's Constructor called: Value of i: " << i << endl; 
		} 

		// Class B contains object of A 
		class B { 
			A a; 
		public: 
			B(int, int ); 
		}; 
	
		B::B(int x, int y): a(x, y){ //Initializer list must be used, otherwise it will try to call default constructor of class A.
			cout << "B's Constructor called"; 
		} 
	
		int main() { 
			B obj(10,20); 
			return 0; 
		}
	4) To initialize the members of Base class.
		Ex:
		#include <iostream> 
		using namespace std; 
	
		class A { 
			int i; 
		public: 
		A(int ); 
		}; 
	
		A::A(int arg) { 
			i = arg; 
			cout << "A's Constructor called: Value of i: " << i << endl; 
		} 
	
		// Class B is derived from A 
		class B: A { 
		public: 
			B(int ); 
		}; 
	
		B::B(int x):A(x) { //Initializer list must be used 
			cout << "B's Constructor called"; 
		} 
	
		int main() { 
			B obj(10); 
			return 0; 
		}
	5) To initialize base class data members if function parameter and data member are using same name.
		//Initialize member variables in initializer list in same order used in class.
