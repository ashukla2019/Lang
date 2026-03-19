'''
Class and Objects
In Python, everything is an object. A class is a blueprint for the object. To create an object we require a model or plan or blueprint which is nothing but class.

For example, you are creating a vehicle according to the Vehicle blueprint (template). The plan contains all dimensions and structure. Based on these descriptions, we can construct a car, truck, bus, or any vehicle. Here, a car, truck, bus are objects of Vehicle class

Class Attributes and Methods:
When we design a class, we use instance variables and class variables.

In Class, attributes can be defined into two parts:

Instance variables: The instance variables are attributes attached to an instance of a class. We define instance variables in the constructor ( the __init__() method of a class).
Class Variables: A class variable is a variable that is declared inside of class, but outside of any instance method or __init()__ method.
Inside a Class, we can define the following three types of methods.

Instance method: Used to access or modify the object attributes. If we use instance variables inside a method, such methods are called instance methods.
Class method: Used to access or modify the class state. In method implementation, if we use only class variables, then such type of methods we should declare as a class method.
Static method: It is a general utility method that performs a task in isolation. Inside this method, we don’t use instance or class variable because this static method doesn’t have access to the class attributes.

'''

class Employee:
    # class variables
    company_name = 'ABC Company'

    # constructor to initialize the object
    def __init__(self, name, salary):
        # instance variables
        self.name = name
        self.salary = salary

    # instance method
    def show(self):
        print('Employee:', self.name, self.salary, self.company_name)

# create first object
emp1 = Employee("Harry", 12000)
emp1.show()

# create second object
emp2 = Employee("Emma", 10000)
emp2.show()
