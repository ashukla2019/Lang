#include <iostream>
using namespace std;

/***********************************Case 1:************************************
class B inherits class A and we don't call any constructor of class A in 
initializer list of class B. 
*/

class A 
{
protected:
	int x;
public:
	A()
	{
		cout<<"A::default ctor\n";
	}
	A(int x):x(x)
	{
		cout<<"A::parameterized ctor\n";
	}
	A(const A& a)
	{
	    cout<<"A::copy ctor\n";
	    x = a.x;
	    
	}
	A& operator=(const A& a)
	{
		cout<<"A::assignment operator\n";
	}
	~A(){}
};

class B: public A
{
	int y;
public:
	B(){"B::default ctor\n";}
	B(int y)
	{
		cout<<"B::parameterized ctor\n";
	}
	B(const B& b)
	{
	    cout<<"B::copy ctor\n";
	    
	}
	B& operator=(const B& b)
	{
	    cout<<"B::assignment operator\n";
	    
	}
	void print()
	{
	    cout<<"A::x="<<x<<endl;
	}
};

int main()
{
	B b1(10); /*O/P: A::default ctor ,B::parameterized ctor */
			   /*
	           B inherits class A and when we call B b1(10), first memory is allocated 
			   for class A and it calls first A's default constructor to initialize A::x 
			   as we did not call any constructor in initializer list of class B and then
			   B's parameterized ctor is called.
	          */
	b1.print(); /*A::x=0 :initialized value in A::A()*/
	B b2 = b1; /* O/P: A::default ctor ,B::copy ctor */
				/*
				B inherits class A and when we call B b2 =b1, this call goes to B's copy ctor
	            and calls first A's default constructor to initialize A::x as we did not call any constructor
	            in initializer list of class B.
				*/
	b2.print(); /* A::x=0*/
	B b3(20); //A::default ctor, B::parameterized ctor
				/*
	            B inherits class A and when we call B b1(10), this call goes to B's parameterized
	            constructor and calls first A's default constructor to initialize A::x 
			    as we did not call any constructor in initializer list of class B and then
			    B's parameterized ctor is called.
	            */
	b3 = b1; //B::assignment operator
	b3.print();
	return 0;
}

/******************************Case 2**************************************

Case 2: class B inherits class A and we call constructor of class A in 
initializer list of class B.
*/

class A 
{
protected:
	int x;
public:
	A()
	{
		cout<<"A::default ctor\n";
	}
	A(int x):x(x)
	{
		cout<<"A::parameterized ctor\n";
	}
	A(const A& a)
	{
	    cout<<"A::copy ctor\n";
	    x = a.x;
	    
	}
	A& operator=(const A& a){cout<<"A::assignment operator\n";}
	~A(){}
};

class B: public A
{
	int y;
public:
	B(){"B::default ctor\n";}
	B(int y):A(10)
	{
		cout<<"B::parameterized ctor\n";
	}
	B(const B& b):A(b.x)  //will call A::A(int) 
	{
	    cout<<"B::copy ctor\n";
	    
	}
	/*
	B(const B& b):A(b)  //will call A::A(const A&) 
	{
	    cout<<"B::copy ctor\n";
	    
	}  */
	B& operator=(const B& b)
	{
	    cout<<"B::assignment operator\n";
	    
	}
	void print()
	{
	    cout<<"A::x="<<x<<endl;
	}
};

int main()
{
	B b1(10);/* O/P: A::parameterized ctor ,B::parameterized ctor */
	/*since class B is inheriting class A, when we create object of class B
	first memory is allocated for class A and then parameterized constructor of class A 
	is called, as we call any parameterized constructor of class A in initializer list 
	of class B. Value assigned in default constructor of class A will be assigned to member of 
	class A. Now memory is allocated for class B and B's class parameterized 
	ctor is called.*/
	b1.print();
	B b2 = b1; 
	b2.print();
	/*we are initializing the b2 object using b1 object. Since we have called parameterized ctor of class A
	in initializer list of B::B(const B&), first parameterized ctor of A is called to initialize
	x variable of b2 as we have called it in initializer list of B::B(const B&) 
	and then copy ctor of class B will be called.*/
	B b3(20);
	b3 = b1; 
	b3.print();
	/*we are copying b1 object to b3 object. Since, we can not any ctor of A in assignment operator call.*/
	return 0;
}
