#include <iostream>
template<typename ... T>
auto sum(T ... t) 
{
	return (t + ...);
}
int main() 
{
  std::cout << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
}

Internal working:
template<>
int sum<int, int, int, int, int, int, int, int, int, int>(int __t0, int __t1, int __t2, int __t3, int __t4, int __t5, int __t6, int __t7, int __t8, int __t9)
{
  return __t0 + (__t1 + (__t2 + (__t3 + (__t4 + (__t5 + (__t6 + (__t7 + (__t8 + __t9))))))));
}
#endif

int main()
{
  std::cout.operator<<(sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)).operator<<(std::endl);
  return 0;
}
----------------------------------------------------------------------------
auto sum(T ... t) 
{
	return (...+t);
}
int main() 
{
std::cout << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
}

template<>
int sum<int, int, int, int, int, int, int, int, int, int>(int __t0, int __t1, int __t2, int __t3, int __t4, int __t5, int __t6, int __t7, int __t8, int __t9)
{
  return ((((((((__t0 + __t1) + __t2) + __t3) + __t4) + __t5) + __t6) + __t7) + __t8) + __t9;
}
#endif

int main()
{
  std::cout.operator<<(sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)).operator<<(std::endl);
  return 0;
}

-------------------------------------------------------------------------------------------- 
Examples of Fold Expressions
1. Unary Left Fold
The unary left fold is written as (... op pack). The expression is expanded as:
	
template<typename... Args>
auto sum(Args... args) {
    return (... + args);  // Unary left fold
}

int main() {
    int result = sum(1, 2, 3, 4, 5);  // result = 1 + 2 + 3 + 4 + 5
    return 0;
}

2. Unary Right Fold
The unary right fold is written as (pack op ...). The expression is expanded as:
#include <string>

template<typename... Args>
std::string concatenate(Args... args) {
    return (args + ...);  // Unary right fold
}

int main() {
    std::string result = concatenate(std::string("Hello, "), std::string("World"), std::string("!"));
    // result = "Hello, World!"
    return 0;
}

3. Binary Left Fold
The binary left fold is written as (init op ... op pack). It uses an initial value (init) and expands as:

template<typename... Args>
auto multiply(Args... args) {
    return (1 * ... * args);  // Binary left fold with initial value 1
}

int main() {
    int result = multiply(2, 3, 4);  // result = 1 * 2 * 3 * 4 = 24
    return 0;
}

4. Binary Right Fold
The binary right fold is written as (pack op ... op init). It uses an initial value and expands as:
template<typename... Args>
bool all_true(Args... args) {
    return (args && ... && true);  // Binary right fold with initial value true
}

int main() {
    bool result = all_true(true, true, false);  // result = true && true && false = false
    return 0;
}
