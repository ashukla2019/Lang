Extern templates: 
In traditional C++, templates are instantiated by the compiler only when they are used. In other
words, as long as a fully defined template is encountered in the code compiled in each compilation unit
(file), it will be instantiated. This results in an increase in compile time due to repeated instantiations.
Also, we have no way to tell the compiler not to trigger the instantiation of the template.
To this end, C++11 introduces an external template that extends the syntax of the original mandatory compiler to instantiate a template at a specific location, allowing us to explicitly tell the compiler
when to instantiate the template:
template class std::vector<bool>; // force instantiation
extern template class std::vector<double>; // should not instantiation in current file

The “>”
In the traditional C++ compiler, >> is always treated as a right shift operator. But actually we can
easily write the code for the nested template:
std::vector<std::vector<int>> matrix;
This is not compiled under the traditional C++ compiler, and C++11 starts with continuous right
angle brackets that become legal and can be compiled successfully. Even the following writing can be
compiled by:
template<bool T>
class MagicType {
bool magic = T;
};
// in main function:
std::vector<MagicType<(1>2)>> magic; // legal, but not recommended
Type alias templates
Before you understand the type alias template, you need to understand the difference between
“template” and “type”. Carefully understand this sentence: Templates are used to generate types.
In traditional C++, typedef can define a new name for the type, but there is no way to define a new
name for the template. Because the template is not a type. E.g:
template<typename T, typename U>
class MagicType {
public:
T dark;
U magic;
};
// not allowed
template<typename T>
typedef MagicType<std::vector<T>, std::string> FakeDarkMagic;
C++11 uses using to introduce the following form of writing, and at the same time supports the
same effect as the traditional typedef:

Usually, we use typedef to define the alias syntax: typedef original name new name;, but
the definition syntax for aliases such as function pointers is different, which usually causes a
certain degree of difficulty for direct reading.
typedef int (*process)(void *);
using NewProcess = int(*)(void *);
template<typename T>
using TrueDarkMagic = MagicType<std::vector<T>, std::string>;
int main() {
TrueDarkMagic<bool> you;
}


Variadic templates
The template has always been one of C++’s unique Black Magic. In traditional C++, both a
class template and a function template could only accept a fixed set of template parameters as specified;
C++11 added a new representation, allowing any number, template parameters of any category, and
there is no need to fix the number of parameters when defining.
template<typename... Ts> class Magic;
The template class Magic object can accept an unrestricted number of typename as a formal parameter of the template, such as the following definition:
class Magic<int,
std::vector<int>,
std::map<std::string,
std::vector<int>>> darkMagic;
Since it is arbitrary, a template parameter with a number of 0 is also possible: class Magic<>
nothing;.
If you do not want to generate 0 template parameters, you can manually define at least one template
parameter:
template<typename Require, typename... Args> class Magic;
The variable length parameter template can also be directly adjusted to the template function. The
printf function in the traditional C, although it can also reach the call of an indefinite number of formal
parameters, is not class safe. In addition to the variable-length parameter functions that define class
safety, C++11 can also make printf-like functions naturally handle objects that are not self-contained.
In addition to the use of ... in the template parameters to indicate the indefinite length of the template
28
2.5 Templates CHAPTER 02: LANGUAGE USABILITY ENHANCEMENTS
parameters, the function parameters also use the same representation to represent the indefinite length
parameters, which provides a convenient means for us to simply write variable length parameter functions,
such as:
template<typename... Args> void printf(const std::string &str, Args... args);
Then we define variable length template parameters, how to unpack the parameters?
First, we can use sizeof... to calculate the number of arguments:
#include <iostream>
template<typename... Ts>
void magic(Ts... args) {
std::cout << sizeof...(args) << std::endl;
}
We can pass any number of arguments to the magic function:
magic(); // 0
magic(1); // 1
magic(1, ""); // 2
