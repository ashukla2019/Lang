/*
tuple is a fixed-size collection of heterogeneous values. 
It is a generalization of std::pair.
*/

/*
Operations on tuple :-

1. get(): is used to access the tuple values and modify them, it accepts the index and tuple
name as arguments to access a particular tuple element.

2. make_tuple():is used to assign tuple with values. The values passed should be in order with
the values declared in tuple.


// C++ code to demonstrate tuple, get() and make_pair()
#include<iostream>
#include<tuple> // for tuple
using namespace std;
int main()
{
	// Declaring tuple
	tuple <char, int, float> geek;

	// Assigning values to tuple using make_tuple()
	geek = make_tuple('a', 10, 15.5);

	// Printing initial tuple values using get()
	cout << "The initial values of tuple are : ";
	cout << get<0>(geek) << " " << get<1>(geek);
	cout << " " << get<2>(geek) << endl;

	// Use of get() to change values of tuple
	get<0>(geek) = 'b';
	get<2>(geek) = 20.5;

	// Printing modified tuple values
	cout << "The modified values of tuple are : ";
	cout << get<0>(geek) << " " << get<1>(geek);
	cout << " " << get<2>(geek) << endl;
	cout << tuple_size<decltype(geek)>::value << endl;

	return 0;
}

3. tuple_size :- It returns the number of elements present in the tuple.

//C++ code to demonstrate tuple_size
#include<iostream>
#include<tuple> // for tuple_size and tuple
using namespace std;
int main()
{

	// Initializing tuple
	tuple <char,int,float> geek(20,'g',17.5);

	// Use of size to find tuple_size of tuple
	cout << "The size of tuple is : ";
	cout << tuple_size<decltype(geek)>::value << endl;

	return 0;

}


4. swap() :- The swap(), swaps the elements of the two different tuples.

	// Initializing 1st tuple
    tuple <int,char,float> tup1(20,'g',17.5);
      
    // Initializing 2nd tuple
    tuple <int,char,float> tup2(10,'f',15.5);
	tup1.swap(tup2);

5. tie() :- The work of tie() is to unpack the tuple values into separate variables.
There are two variants of tie(), with and without “ignore” , 
the “ignore” ignores a particular tuple element and stops it from getting unpacked.
*/

// C++ code to demonstrate working of tie()
#include<iostream>
#include<tuple> // for tie() and tuple
using namespace std;
int main()
{
	// Initializing variables for unpacking
	int i_val;
	char ch_val;
	float f_val;
	
	// Initializing tuple
	tuple <int,char,float> tup1(20,'g',17.5);

	// Use of tie() without ignore
	tie(i_val,ch_val,f_val) = tup1;
	
	// Displaying unpacked tuple elements
	// without ignore
	cout << "The unpacked tuple values (without ignore) are : ";
	cout << i_val << " " << ch_val << " " << f_val;
	cout << endl;
	
	// Use of tie() with ignore
	// ignores char value
	tie(i_val,ignore,f_val) = tup1;
	
	// Displaying unpacked tuple elements
	// with ignore
	cout << "The unpacked tuple values (with ignore) are : ";
	cout << i_val << " " << f_val;
	cout << endl;

	return 0;

}

//Vector of tuples
#include <bits/stdc++.h>
using namespace std;
int main() {
    typedef vector< tuple<int, int, int> > my_tuple;
    my_tuple tl; 
    tl.push_back( tuple<int, int, int>(21,20,19) );
    for (my_tuple::const_iterator i = tl.begin(); i != tl.end(); ++i) {
        cout << get<0>(*i) << endl;
        cout << get<1>(*i) << endl;
        cout << get<2>(*i) << endl;
    }
    cout << get<0>(tl[0]) << endl;
    cout << get<1>(tl[0]) << endl;
    cout << get<2>(tl[0]) << endl;

    return 0;
}
--------------------------------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <string>

using namespace std;



int main() {
   //Creating/Initializing tuples:
        tuple<int, int, string>tup1{ 1,2,"AB"};
        tuple<int, int, string>tup2(make_tuple(3, 4, "CD"));

        //Dynamically allocated tuple:
        auto* t = new std::tuple<int, std::string>(1, "hello");

    //Access/Read tuple:
        cout << get<0>(tup1) << endl;
        cout << get<1>(tup1) << endl;
        cout << get<2>(tup1) << endl;

        //Accessing/reading/unpacking/extracting by using tie
        int a, b;
        string s;
        tie(a, b, s) = tup2;
        cout <<a << endl;
        cout << b << endl;
        cout << s << endl;

    //Update tuple value:
        get<0>(tup1) = 10;
        cout << get<0>(tup1) << endl;

        vector<tuple<int, int, string>>vect;
        vect.push_back(make_tuple(10, 20, "ABC"));
        for (auto [X, Y, Z] : vect)
        {
            std::cout << X << " " << Y << " " << Z << std::endl;
        }


   return 0;
}
