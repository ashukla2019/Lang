#include <iostream>

// Since C++14 or later:

void f(auto&& t) 
{
  std::cout<<"T type is"<<typeid(t).name<<std::endl;
}

// Since C++11 or later:
template <typename T>
void f(T&& t) {
  // ...
}

int main()
{
    int x = 0;
    f(0); // T is int, deduces as f(int &&) => f(int&&)
    f(x); // T is int&, deduces as f(int& &&) => f(int&)

    int& y = x;
    f(y); // T is int&, deduces as f(int& &&) => f(int&)

    int&& z = 0; // NOTE: `z` is an lvalue with type `int&&`.
    f(z); // T is int&, deduces as f(int& &&) => f(int&)
    f(std::move(z)); // T is int, deduces as f(int &&) => f(int&&)
}
