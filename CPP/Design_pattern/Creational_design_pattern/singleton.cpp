#include <iostream>
using namespace std;

class Singleton {
private:
    // Private constructor
    Singleton() {
        cout << "Singleton object created\n";
    }

    // Prevent copying
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    // Global access point
    static Singleton& getInstance() {
        static Singleton instance;  // Created only once
        return instance;
    }

    void display() {
        cout << "Hello from Singleton\n";
    }
};

int main() {
    Singleton& obj1 = Singleton::getInstance();
    Singleton& obj2 = Singleton::getInstance();

    obj1.display();
    obj2.display();

    if (&obj1 == &obj2)
        cout << "Both objects are the same instance.\n";

    return 0;
}
