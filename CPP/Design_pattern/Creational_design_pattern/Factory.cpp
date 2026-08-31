#include <iostream>
#include <string>

using namespace std;

class Button {
public:
    virtual void paint() = 0;
    virtual ~Button() = default;
};

class WindowsButton : public Button {
public:
    void paint() override {
        cout << "Windows Button\n";
    }
};

class OSXButton : public Button {
public:
    void paint() override {
        cout << "OSX Button\n";
    }
};

class ButtonFactory {
public:
    static Button* createButton(string type) {
        if (type == "Windows")
            return new WindowsButton();

        if (type == "OSX")
            return new OSXButton();

        return nullptr;
    }
};

int main() {
    Button* b1 = ButtonFactory::createButton("Windows");
    b1->paint();

    Button* b2 = ButtonFactory::createButton("OSX");
    b2->paint();
}
