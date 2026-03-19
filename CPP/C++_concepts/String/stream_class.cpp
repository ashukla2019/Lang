1. std::stringstream — Both Input and Output:
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    stringstream ss;

    ss << "Age: " << 30;
    string result = ss.str();  // get the full string
    cout << "Output: " << result << endl;

    // Read from it
    string label;
    int age;
    ss >> label >> age;
    cout << "Parsed: " << label << ", " << age << endl;

    return 0;
}
-----------------------------------------------------------------------------------------------------------
 2. std::istringstream — Input Only (Reading from Strings)
 #include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    string input = "42 3.14 hello";
    istringstream iss(input);

    int a;
    double b;
    string c;

    iss >> a >> b >> c;

    cout << "Integer: " << a << ", Double: " << b << ", String: " << c << endl;

    return 0;
}
---------------------------------------------------------------------------------------------------------------
3. std::ostringstream — Output Only (Building Strings)
  #include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    ostringstream oss;

    int age = 25;
    string name = "Alice";

    oss << "Name: " << name << ", Age: " << age;

    string result = oss.str();
    cout << result << endl;

    return 0;
}


