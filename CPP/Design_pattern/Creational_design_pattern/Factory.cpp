/*
Factory Design pattern: 
Factory method is a creational design pattern which solves the problem of creating product objects
without specifying their concrete classes.
Factory Method defines a method, which should be used for creating objects instead of 
direct constructor call (new operator). Subclasses can override this method to change the
class of objects that will be created.
*/

#include <iostream>

class Button 
{
public:
        virtual void paint() = 0;
};
 
class OSXButton: public Button
{
public:
        void paint() 
		{
                std::cout << "OSX button \n";
        }
};
 
class WindowsButton: public Button  
{
public:
        void paint() 
		{
                std::cout << "Windows button \n";
        }
};
 
class GUIFactory 
{
public:
        virtual Button *createButton(char *) = 0;
};

class Factory: public GUIFactory 
{    //Factory class
public:
        Button *createButton(char *type) 
		{    //Factory method
                if(strcmp(type,"Windows") == 0) 
				{
                        return new WindowsButton;
                }
                else if(strcmp(type,"OSX") == 0) 
				{
                        return new OSXButton;
                }
        }
};

int main()
{
        GUIFactory* guiFactory;
        Button *btn;

        guiFactory = new Factory;

        btn = guiFactory->createButton("OSX");
        btn -> paint();
        btn = guiFactory->createButton("Windows");
        btn -> paint();

        return 0;
}