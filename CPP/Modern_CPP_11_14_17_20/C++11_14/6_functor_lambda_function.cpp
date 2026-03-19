/*Functors: Calling object using parenthesis like function call. 
One advantage of functors over function pointers is that they can hold state. 
Since this state is held by the instance of the object it can be thread safe 
(unlike static variables inside functions used with function pointers). 
The state of a functor can be initialized at construction.

function pointer can not have additional value/state:
*/
void print(int val)
{
    cout << "val:" << val << endl;
}

class printVal
{
    int val;
public:
    printVal() = default;
    printVal(int val):val(val){}
    void operator()(int x) {
        if (x > val)
            cout << "value greater than default set value" << x << endl;
    }
};


int main()
{
    vector<int>vec{ 10, 20, 30, 40 };
    //using function pointer
    void (*func_ptr)(int) = &print;
    for_each(vec.begin(), vec.end(), func_ptr);
    //Using normal function
    for_each(vec.begin(), vec.end(), print);
    //We can not pass additional variable or state using function or function pointer
    //we should functor:
    printVal p(10);
    for_each(vec.begin(), vec.end(), p);
    return 0;
}

--------------------------------------------------------------
Lambda function: C++ Lambda expression allows us to define anonymous function objects (functors) which can 
either be used inline or passed as an argument.	
syntax: []()<mutable> <exception> <constexpr> <return_type>
{
	
}
If mutable/exception/constexpr specification used, Parameter list () becomes mandatory.

	1) Basic lambda example:
	#include <iostream>
	int main() {
	    auto greet = []() { std::cout << "Hello, Lambda!\n"; };
	    greet();
	}
       ------------------------------------------
	2) Lambda with Parameters
	auto add = [](int a, int b) { return a + b; };
	std::cout << add(3, 4);  // Output: 7
       ------------------------------------------
	3) Lambda with Return Type
 	auto divide = [](double a, double b) -> double {
    	if (b == 0) return 0;
    	return a / b;
	};
       -------------------------------------------------
	4) Capture by Value [=]
	int x = 5;
	auto print = [=]() { std::cout << x << "\n"; };
	print();  // Output: 5
     ---------------------------------------------------
	5) Capture by Reference [&]
	int x = 5;
	auto modify = [&]() { x = 10; };
	modify();
	std::cout << x;  // Output: 10
   -------------------------------------------------------
	6) Mixed Capture
        int a = 1, b = 2;
	auto lam = [a, &b]() {
    	// a captured by value, b by reference
    	std::cout << a << " " << b << "\n";
	};
--------------------------------------------------------------
	7) Mutable Lambdas
	int x = 10;
	auto lam = [x]() mutable {
    	x++;
    	std::cout << x << "\n";  // Output: 11
	};
	lam();
	std::cout << x << "\n";  // Output: 10 (original remains unchanged)
------------------------------------------------------------------------------
	8) Generic Lambdas (C++14+)
        auto add = [](auto a, auto b) {
    	return a + b;
	};
	std::cout << add(1, 2) << "\n";      // 3
	std::cout << add(1.1, 2.2) << "\n";  // 3.3
-----------------------------------------------------------------------------
	9) Lambdas in STL Algorithms
	#include <algorithm>
	#include <vector>
	#include <iostream>

	int main() {
    	std::vector<int> v = {1, 2, 3, 4, 5};
	std::for_each(v.begin(), v.end(), [](int n) {
        std::cout << n << " ";
    	});
	}
-------------------------------------------------------------------------------
	10) Lambda as Function Pointer
        #include <iostream>
	void callFunc(void (*func)()) {
    	func();
	}

	int main() {
    	auto lam = []() { std::cout << "Function called\n"; };
    	callFunc(lam);  // Works only if lambda does not capture anything
	}
----------------------------------------------------------------------------------
	11) Storing Lambdas with std::function
	#include <functional>

	std::function<int(int, int)> func = [](int a, int b) {
    	return a + b;
	};
	std::cout << func(5, 3);  // Output: 8
-----------------------------------------------------------------------------------
	12) [this] — Captures Object by Reference
	#include <iostream>
	class MyClass {
    	int value = 10;
	public:
    	void show() {
        auto lambda = [this]() {
            std::cout << "Value: " << value << "\n";  // accesses value via this
        };
        value = 20;
        lambda();  // Output: Value: 20
    	}
	};
------------------------------------------------------------------------------------
	13)  [*this] — Captures Object by Value (Copy)
	#include <iostream>

	class MyClass {
    	int value = 10;
	public:
    	void show() {
        auto lambda = [*this]() {
            std::cout << "Value: " << value << "\n";  // works on a copy of *this
        };
        value = 20;
        lambda();  // Output: Value: 10
    	}
	};

------------------------------------------------------------------------------------
	14) IIFE with Lambda (Immediately Invoked Function Expression)
	int result = [](int x, int y) {
    	return x + y;
	}(5, 3);  // result = 8
--------------------------------------------------------------------------------------
	15) Constexpr Lambdas (C++17+)
	auto outer = [](int a) {
    	return [a](int b) {
        return a + b;
    	};
	};

	auto inner = outer(10);
	std::cout << inner(5);  // Output: 15
-----------------------------------------------------------------------------------------
	26) Simple Generic Lambda
        #include <iostream>

	int main() {
    	auto add = [](auto x, auto y) {
        return x + y;
    	};

    	std::cout << add(3, 4) << "\n";         // 7 (int)
    	std::cout << add(2.5, 1.5) << "\n";     // 4.0 (double)
    	std::cout << add(std::string("Hi "), "there") << "\n";  // "Hi there"
	}






