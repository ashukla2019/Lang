#include <iostream>
using namespace std;

// function to check for integar value
template <typename C> 
void printInfo(const C& value)
{
    // if the value is not integer, the if block will be
    // discarded
    if constexpr (is_integral_v<C>) {
        cout << "Integer Value " << value << endl;
    }
    // if the value is integer, the else block will be
    // discarded
    else {
        cout << "Non-Integer value:" << value << endl;
    }
}

// driver code
int main()
{
    printInfo(10.0);
    printInfo(3.15);
}
