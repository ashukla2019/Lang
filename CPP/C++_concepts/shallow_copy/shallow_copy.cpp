#include <iostream>
using namespace std;

class Student {
public:
    int* marks;

    Student(int m) {
        marks = new int(m);
    }
	Student(const Student& s) //deep copy, if not provided then code will try to call shallow copy and it will free twice.
	{
		marks = new int();
		*marks = *s.marks;
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
