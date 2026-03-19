//Override and Final:
	//Override:
	
	class B 
	{
	public:
	   virtual void f(int) const {std::cout << "B::f " << std::endl;}
	};

	class D : public B
	{
	public:
	   virtual void f(int) {std::cout << "D::f" << std::endl;}
	};
	int main()
	{
		B *b = new D();
		b->f(1); --> this will call base class f() not derived class f(). Since derive class function is not overriding the base class function. Both the functions are different in signature.
	}

	//if we want to avoid such situation, we will declare derive class function as override, now compiler will give you an error here. 
	Example with override implementation:
	class B 
	{
	public:
	   virtual void f(int) const 
	   {std::cout << "B::f " << std::endl;}
	};

	class D : public B
	{
	public:
	   virtual void f(int) override 
	   {std::cout << "D::f" << std::endl;}
	};
	
//Final: final can be used for 2 purpose:
	//1) Sometimes you don’t want to allow derived class to override the 
	//base class’ virtual function. C++ 11 allows built-in facility to prevent 
	//overriding of virtual function using final specifier
		
	class B 
	{
	public:
	   virtual void f(int) final //Freezed member-function, can not be overridden in sub-class
	   {std::cout << "B::f " << std::endl;}
	};

	class D : public B
	{
	public:
	   virtual void f(int)  
	   {std::cout << "D::f" << std::endl;}
	};
	
	//2) final specifier in C++ 11 can also be used to prevent inheritance of 
	//class / struct. If a class or struct is marked as final then it becomes non 
	//inheritable and it cannot be used as base class/struct. 
	class Base final
	{
	};
 
	class Derived : public Base
	{
	};
 
	int main()
	{
		Derived d;
		return 0;
	
	}
	//o/p: error: cannot derive from ‘final’ base ‘Base’ in derived type ‘Derived’
    //class Derived : public Base