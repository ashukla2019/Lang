template argument deduction for class templates: 
----------------------------------------------------------------------
Before C++17, when you instantiated a class template, you had to specify the template arguments explicitly:
template<typename T, typename U>
struct Pair {
    T first;
    U second;
};
Pair<int, double> p1{42, 3.14}; // C++11/C++14 — explicit types
-----------------------------------------------------------------------------------
In C++17, you can omit the template arguments:
Pair p2{42, 3.14}; // C++17 — deduced as Pair<int, double>
----------------------------------------------------------------------------------
