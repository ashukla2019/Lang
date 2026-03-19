/*Deleted and Defaulted Functions: The default part instructs the compiler to generate the default implementation for
  the function. Defaulted functions have two advantages: 
  They are more efficient than manual implementations, and they rid the programmer from the chore 
  of defining those functions manually.
  */
  struct A
	{
		A()=default; //C++11
		virtual ~A()=default; //C++11
	};
  The opposite of a defaulted function is a deleted function:
  int func()=delete;
  Deleted functions are useful for preventing object copying, among the rest. 
  Recall that C++ automatically declares a copy constructor and an assignment operator for classes. 
  To disable copying, declare these two special member functions =delete:
  class A {
	public:
    A(int x): m(x)
    {
    }
     
    // Delete the copy constructor
    A(const A&) = delete;
     
    // Delete the copy assignment operator
    A& operator=(const A&) = delete;
    int m;
};

