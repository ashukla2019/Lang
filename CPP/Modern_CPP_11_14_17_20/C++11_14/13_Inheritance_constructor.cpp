Inheritance constructor
In traditional C++, constructors need to pass arguments one by one if they need inheritance, which
leads to inefficiency. C++11 introduces the concept of inheritance constructors using the keyword using:
#include <iostream>
class Base {
public:
int value1;
32
2.6 Object-oriented CHAPTER 02: LANGUAGE USABILITY ENHANCEMENTS
int value2;
Base() {
value1 = 1;
}
Base(int value) : Base() { // delegate Base() constructor
value2 = value;
}
};
class Subclass : public Base {
public:
using Base::Base; // inheritance constructor
};
int main() {
Subclass s(3);
std::cout << s.value1 << std::endl;
std::cout << s.value2 << std::endl;
}
