#include <iostream>
#include <string>

using namespace std;

class Engine
{
    int power;

public:
    Engine()
    {
        cout << "Engine Default Constructor\n";
    }

    Engine(int power) : power(power)
    {
        cout << "Engine Parameterized Constructor\n";
    }

    Engine(const Engine& e) : power(e.power)
    {
        cout << "Engine Copy Constructor\n";
    }

    Engine& operator=(const Engine& e)
    {
        cout << "Engine Assignment Operator\n";

        if (this != &e)
            power = e.power;

        return *this;
    }

    ~Engine()
    {
        cout << "Engine Destructor\n";
    }
};

class Car
{
    int model;
    string name;
    Engine eng;

public:

    Car(string name, int model, const Engine& eng1)

        // ==============================
        // Option 1 (Recommended)
        // Calls Engine Copy Constructor
        // ==============================
        : model(model), name(name), eng(eng1)

        // ==============================
        // Option 2
        // Uncomment this initializer and
        // comment the above initializer.
        //
        // Engine Default Constructor
        // will be called first because
        // eng isn't initialized.
        //
        // Then assignment operator will
        // be called inside constructor.
        // ==============================
        // : model(model), name(name)
    {
        // Uncomment this only when using
        // Option 2 above.

        // eng = eng1;      // Engine Assignment Operator

        cout << "Car Constructor\n";
    }

    ~Car()
    {
        cout << "Car Destructor\n";
    }
};

int main()
{
    Engine e(100);

    cout << "-------------------------\n";

    Car c("BMW",101,e);

    cout << "-------------------------\n";

    return 0;
}
