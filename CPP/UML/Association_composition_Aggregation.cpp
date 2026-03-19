Association in C++ is a relationship between two classes where one class uses the functionalities
provided by the other class. In other words, an association represents the connection or
link between two classes. In an association, one class instance is connected to one or more 
instances of another class.

Example of Association in C++:
class Bank 
{
public:
    void transferMoney(Account* fromAccount, Account* toAccount, double amount) 
   {
        // Code to transfer money from one account to another
    }
};

class Account 
{
public:
    Account(int id, double balance) : id(id), balance(balance) {}
    int getId() { return id; }
    double getBalance() { return balance; }
private:
    int id;
    double balance;
};

int main() 
{
    Account* account1 = new Account(123, 1000.00)
    Account* account2 = new Account(456, 500.00);
    Bank bank;
    bank.transferMoney(account1, account2, 250.00);
    return 0;
}
In this example, we have two classes: Bank and Account. Bank class has a transferMoney() method
that takes two Account objects and a double value representing the amount of money to be 
transferred from one account to another. Bank class is associated with the Account class, 
meaning that it has a connection or a link to the Account class.
In the main() function, we create two Account objects with different IDs and balances, and then
we create an instance of the Bank class. We then call the transferMoney() method of the Bank 
class and pass it the two Account objects and the amount of money to be transferred.
As we can see, the Bank class has a direct association with the Account class because 
it uses objects of the Account class as parameters in its method.

------------------------------------------------------------------------------------------
Composition:
Composition is a relationship between two classes in which one class, known as the composite
class, contains an object of another class, known as the component class, as a member variable.
The composite class owns the component class, and the component class cannot exist 
independently of the composite class. In other words, the lifetime of the component class
is controlled by the composite class.

Example of Composition in C++:
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

In this example, we have two classes: Engine and Car. The Car class is composed of an Engine
object. The Engine object is an essential part of the Car object, and if the Car object is 
destroyed, the Engine object will also be destroyed.
In the Car class constructor, we create a new instance of the Engine class and store it in 
a pointer variable named engine. We then provide a method named startCar() in the Car class,
which calls the start() method of the Engine object stored in the engine pointer.
In the main() function, we create a new instance of the Car class and call the startCar() 
method to start the car. As we can see, the Car class is composed of an Engine object, 
and the startCar() method of the Car class uses the Engine object to start the car.
-----------------------------------------------------------------------------------
Aggregation:
Aggregation is a relationship between two classes in which one class, known as the aggregate
class, contains a pointer or reference to an object of another class, known as the component 
class. The component class can exist independently of the aggregate class, and it can be 
shared by multiple aggregate classes. In other words, the lifetime of the component class is
not controlled by the aggregate class.

Example of Aggregation in C++:

class Person {
public:
    Person(std::string name) : name(name), address(nullptr) {}
    void setAddress(Address* address) {
        this->address = address;
    }
private:
    std::string name;
    Address* address;
};

class Address {
public:
    Address(std::string street, std::string city, std::string state, std::string zip)
        : street(street), city(city), state(state), zip(zip) {}
private:
    std::string street;
    std::string city;
    std::string state;
    std::string zip;
};

int main() {
    Address* address = new Address("123 Main St.", "Anytown", "CA", "12345");
    Person person("John Doe");
    person.setAddress(address);
    return 0;
}
In this example, we have two classes: Person and Address. The Person class has a member variable named address, which is a pointer to an Address object. The Address object is not an essential part of the Person object, and if the Person object is destroyed, the Address object will not be destroyed.
In the main() function, we create a new Address object and store it in a pointer variable named address. We then create a new instance of the Person class and pass it the name “John Doe”. We then call the setAddress() method of the Person class and pass it the address pointer. This sets the address of the Person object to the address object we created earlier.
As we can see, the Person class has an aggregation relationship with the Address class because the Person object contains a pointer to the Address object, but the Address object is not an essential part of the Person object.
--------------------------------------------------------------------------------------
Association, Composition, and Aggregation are three fundamental concepts in Object-Oriented 
Programming that describe the relationship between classes and objects.
Association: Association is a relationship between two classes that defines a connection or 
a link between them. The association can be bi-directional, meaning that both classes can 
use each other’s methods and properties, or uni-directional, where only one class can use 
the methods and properties of the other. The relationship can be of any type, such as a 
one-to-one, one-to-many, or many-to-many. For example, a Customer class might be associated
with an Order class, where each customer can have multiple orders.

Composition: Composition is a relationship between two classes where one class is composed of
one or more instances of the other class. The composed class is typically an essential part
of the composite class, and if the composite class is destroyed, the composed class will 
also be destroyed. For example, a House class might be composed of a Room class, where 
the Room class cannot exist without the House class.

Aggregation: Aggregation is similar to composition in that it represents a relationship 
between two classes where one class is composed of one or more instances of the other 
class. However, in aggregation, the composed class is not an essential part of the composite
class, and it can exist independently. For example, a University class might have an 
aggregation relationship with a Student class, where the Student class can exist 
independently of the University class.

In summary, Association is a relationship between two classes that defines a connection 
or a link between them. Composition is a relationship where one class is composed of one
or more instances of the other class, and the composed class is an essential part of the 
composite class. Aggregation is a relationship where one class is composed of one or 
more instances of the other class, and the composed class is not an essential part 
of the composite class.

