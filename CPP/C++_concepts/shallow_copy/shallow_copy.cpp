#include <iostream>
using namespace std;

class Student {
public:
    int* marks;

    Student(int m) {
        marks = new int(m);
    }

    ~Student() {
        delete marks;
    }
};

int main() {
    Student s1(90);

    Student s2 = s1;   // Shallow copy

    cout << *s1.marks << endl;
    cout << *s2.marks << endl;

    *s2.marks = 50;

    cout << "s1: " << *s1.marks << endl;
    cout << "s2: " << *s2.marks << endl;
}
