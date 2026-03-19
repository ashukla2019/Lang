/*
Aggregation(By reference):  Type of association. I have an object which I have borrowed 
from someone else. Independent. One object will carry reference of another object. 
One object destroy, other will not destroy. weak relationship.
Example: Person object has reference of Car object. If person object is destroyed,
Car object will not be destroyed.
*/

#include <iostream>
#include <string>
using namespace std;

class Car
{	int model;
	string name;
	public:
	Car(string name, int model): name(name), model(model){}
	void printCarInfo()
	{
	 	cout<<model<<name<<endl;
	}
};
class Person
{
	string name;
	Car *mycar;
	public:
	Person() = default;
	Person(string name, Car* mycar):name(name), mycar(mycar)
	{
	}
};
int main()
{
	Car c ("BMW", 134);
	Person *p = new Person("Ankit", &c);
	delete p; //It will delete only person object but Car object will not be deleted.
	c.printCarInfo();
	return 0;
}
