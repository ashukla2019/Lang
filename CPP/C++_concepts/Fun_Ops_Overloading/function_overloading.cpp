#include <iostream>
using namespace std;

void print(int i) 
{
	cout << " Here is int " << i << endl;
}
void print(double f) 
{
	cout << " Here is float " << f << endl;
}
void print(char const *c) 
{
	cout << " Here is char* " << c << endl;
}

int main() {
print(10);
print(10.10);
print("ten");
return 0;
}

//Functions cannot be overloaded if they differ only in the return type

int foo() {
return 10;
}

char foo() {
return 'a';
}

int main()
{
char x = foo();
getchar();
return 0;
}

//Function overloading and const keyword:
//C++ allows functions to be overloaded on the basis of const-ness of parameters
//only if the const parameter is a reference or a pointer. 
//That is why the program 1 failed in compilation, but the program 2 worked fine. 
//Prog1:
void fun(const int i)
{
    cout << "fun(const int) called ";
}
void fun(int i)
{
    cout << "fun(int ) called " ;
}
int main()
{
    const int i = 10;
    fun(i);
    return 0;
}
Compiler Error: redefinition of 'void fun(int)'

// PROGRAM 2 (Compiles and runs fine)

void fun(char *a)
{
cout << "non-const fun() " << a;
}

void fun(const char *a)
{
cout << "const fun() " << a;
}

int main()
{
const char *ptr = "GeeksforGeeks";
fun(ptr);
return 0;
}

