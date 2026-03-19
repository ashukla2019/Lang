C++ provides a powerful alternative for the char*. It is not a built-in data type, but is a container class in the 
Standard Template Library. String class provides different string manipulation functions like concatenation, 
find, replace etc. Let us see how to construct a string type.

string s0;                                       // s0 = “”
string s1(“Hello”);                               // s1 = “Hello”
string s2 (s1);                                  // s2 = “Hello”
string s3 (s1, 1, 2);                            // s3 = “el”
string s4 ("Hello World", 5);                     // s4 = “Hello”
string s5 (5, ‘*’);                              // s5 = “*****”
string s6 (s1.begin(), s1.begin()+3);              // s6 = “Hel”

Here are some member functions:
append(): Inserts additional characters at the end of the string (can also be done using ‘+’ or ‘+=’ operator). Its time complexity is O(N) where N is the size of the new string.
assign(): Assigns new string by replacing the previous value (can also be done using ‘=’ operator).
at(): Returns the character at a particular position (can also be done using ‘[ ]’ operator). Its time complexity is O(1).
begin(): Returns an iterator pointing to the first character. Its time complexity is O(1).
clear(): Erases all the contents of the string and assign an empty string (“”) of length zero. Its time complexity is O(1).
compare(): Compares the value of the string with the string passed in the parameter and returns an integer accordingly. Its time complexity is O(N + M) where N is the size of the first string and M is the size of the second string.
copy(): Copies the substring of the string in the string passed as parameter and returns the number of characters copied. Its time complexity is O(N) where N is the size of the copied string.
c_str(): Convert the string into C-style string (null terminated string) and returns the pointer to the C-style string. Its time complexity is O(1).
empty(): Returns a boolean value, true if the string is empty and false if the string is not empty. Its time complexity is O(1).
end(): Returns an iterator pointing to a position which is next to the last character. Its time complexity is O(1).
erase(): Deletes a substring of the string. Its time complexity is O(N) where N is the size of the new string.
find(): Searches the string and returns the first occurrence of the parameter in the string. Its time complexity is O(N) where N is the size of the string.
insert(): Inserts additional characters into the string at a particular position. Its time complexity is O(N) where N is the size of the new string.
length(): Returns the length of the string. Its time complexity is O(1).
replace(): Replaces the particular portion of the string. Its time complexity is O(N) where N is size of the new string.
resize(): Resize the string to the new length which can be less than or greater than the current length. Its time complexity is O(N) where N is the size of the new string.
size(): Returns the length of the string. Its time complexity is O(1).
substr(): Returns a string which is the copy of the substring. Its time complexity is O(N) where N is the size of the substring.

Implementation:

#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    string s, s1;
    s = "HELLO";
    s1 = "HELLO";
    if(s.compare(s1) == 0)
        cout << s << " is equal to " << s1 << endl;
    else
        cout << s << " is not equal to " << s1 << endl;
    s.append(" WORLD!");
    cout << s << endl;
    printf("%s\n", s.c_str());
    if(s.compare(s1) == 0)
        cout << s << " is equal to " << s1 << endl;
    else
        cout << s << " is not equal to " << s1 << endl;
    return 0;
}
Output:

HELLO is equal to HELLO
HELLO WORLD!
HELLO WORLD!
HELLO WORLD! is not equal to HELLO
