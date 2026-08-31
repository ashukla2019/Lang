#include <iostream>
#include <string>

using namespace std;

class Pizza {
public:
    virtual void prepare() = 0;
    virtual ~Pizza() = default;
};

class MargheritaPizza : public Pizza {
public:
    void prepare() override {
        cout << "Preparing Margherita Pizza\n";
    }
};

class PepperoniPizza : public Pizza {
public:
    void prepare() override {
        cout << "Preparing Pepperoni Pizza\n";
    }
};

class PizzaFactory {
public:
    static Pizza* createPizza(string type) {
        if (type == "Margherita")
            return new MargheritaPizza();

        if (type == "Pepperoni")
            return new PepperoniPizza();

        return nullptr;
    }
};

int main() {
    Pizza* p1 = PizzaFactory::createPizza("Margherita");
    p1->prepare();

    Pizza* p2 = PizzaFactory::createPizza("Pepperoni");
    p2->prepare();
}
