#constexpr lambda: A constexpr lambda is a lambda function that can be evaluated at compile-time if the input allows.

#include <iostream>

int main() {
    constexpr auto add = [](int a, int b) {
        return a + b;
    };

    constexpr int x = add(2, 3); // compile-time calculation

    std::cout << "x = " << x << '\n'; // x = 5
}

