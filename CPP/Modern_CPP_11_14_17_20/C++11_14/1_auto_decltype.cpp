//Before C++11, the auto keyword was used for storage class.
//auto is now a sort of placeholder for a type, telling the compiler it has to deduce the actual type 
//of a variable that is being declared from its initializer. 
1) Auto type deduction:
	auto i = 42;        // i is an int
	auto l = 42LL;      // l is an long long
	auto p = new foo(); // p is a foo*

2) Type deduction with braced initializers (C++14)
	auto A = { 1, 2 }; // std::initializer_list<int>
	auto B = { 3 }; // std::initializer_list<int>
	auto C{ 4 }; // int
	auto D = { 5, 6.7 }; // C3535: cannot deduce type for 'auto' from initializer list'	
	auto i = 10+5;
	1) compile time: to fetch the result type of expression(10+5), which will be int.
	2) run time: to evaluate the expression at run time and assign it to i. 
	If we just want to check type of expression, we can use decltype. which will identify at compile time.
	decltype(
	//auto retVal = gfun(45, 4.5f);
	decltype(gfun(45, 4.5f)) retVal;

3) auto can be used for iterators also.
	vector<int>::iterator it; //old way
	for(auto it = begin(map); it != end(map); ++it)  -->auto it will automatically will take type
	{
	}

4) Function return type deduction is implemented in C++14:
	auto Correct(int i)
	{
	  if (i == 1)
		return i;             // return type deduced as int

	  return Correct(i-1)+i;  // ok to call it now
	}
	//Don't use auto: when type conversion is needed...

5) When want function return type same as expression:
//Decltype: It checks the type of expression
#include<iosteam>
using namespace std;

template<typename T1, typename T2>
T2 sum(T1 a, T2 b)
{
	return(a+b);
} 

int main()
{
	cout<<sum(1, 1.8)<<endl;  //this will print 2.8(T2 is float type)
	cout<<sum(1.8, 1)<<endl;  //this will print 2(T2 is integer type)
	return 0;
}

//Solution with decltype:
template<typename T1, typename T2>
auto sum(T1 a, T2 b)->decltype(a+b)
{
	return(a+b);
} 

int main()
{
	cout<<sum(1, 1.8)<<endl;  //decltype is just checking the type of expression and same is returned.
	cout<<sum(1.8, 1)<<endl;  //decltype is just checking the type of expression and same is returned.
	return 0;
} 

problem: return type also required..
template<typename R, typename T, typename U>
R add(T x, U y) {
return x+y;
}

solution is auto with decltype...

auto can not be used for function arguments:
int add(auto x, auto y): ->wrong

auto can not be used for type derivation:
auto auto_arr[10] = {arr};
------------------------------------------------------
decltype(auto):
The decltype(auto) type-specifier also deduces a type like auto does. 
However, it deduces return types while keeping their references and cv-qualifiers, 
while auto will not.

const int x = 0;
auto x1 = x; // int
decltype(auto) x2 = x; // const int
int y = 0;
int& y1 = y;
auto y2 = y1; // int
decltype(auto) y3 = y1; // int&
int&& z = 0;
auto z1 = std::move(z); // int
decltype(auto) z2 = std::move(z); // int&&
	


