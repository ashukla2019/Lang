/*
Composition(composed inside other class):  Type of association. Dependent. 
One object will carry another object as a value. One object destroy, 
other will also destroy. Strong relationship.
Example: Car object has Engine object. If Car object is destroyed, 
Engine object will be destroyed.
*/

#include <iostream>
#include <string>
using namespace std;
class Engine
{
	int power;
	public:
	Engine(){}
	Engine(int power):power(power)
	{
		cout<<"Engine object is created"<<endl;
	}
	Engine(const Engine& e)
	{
		cout<<"Engine::Copy ctor is called"<<endl;
	}
	Engine& operator=(const Engine& e)
	{
		cout<<"Engine::assignment operator is called"<<endl;
	}
	~Engine()
	{
		cout<<"Engine object is destroyed"<<endl;
	}
};
class Car
{
	int model;
	string name;
	Engine eng;
	public:
	//If we don't call Engine::Engine(const Engine&), then Engine::Engine() will be called
	//to initialize Engine object of class Car.
	Car(string name, int model, Engine eng1): name(name), model(model),eng(eng1) //will call copy ctor of Engine
	{
		//eng = eng1; //will call assignment operator
		cout<<"Car object is created"<<endl;
	}
	Car(const Car& c):eng(c.eng)///will call copy ctor of Engine
	{
		//eng = c.eng; //will call assignment operator
		cout<<"Car object is created"<<endl;
	}
	~Car()
	{
		cout<<"Car object is destroyed"<<endl;
	}
};
int main()
{
	Engine e(10);
	/*Car *c = new Car ("BMW", 134, e);
	delete c;*/
	Car c("BMW", 134, e);
	Car c1 = c;
	return 0;
}
