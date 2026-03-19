Class Method in Python: Class methods are associated with the class rather than instances. They are defined using the @classmethod
decorator and take the class itself as the first parameter, usually named cls. Class methods are useful for tasks that involve the
class rather than the instance, such as creating class-specific behaviors or modifying class-level attributes.

Syntax Python Class Method:
class C(object):
    @classmethod
    def fun(cls, arg1, arg2, ...):
       ....
fun: function that needs to be converted into a class method
returns: a class method for function.
In this example, the MyClass defines a class variable class_variable, and the class_method is a class method that increments this variable. When calling the method with different values, it updates and returns the modified class variable. Instances obj1 and obj2 have their own instance_variable.

code:
class MyClass:
    class_variable = 0

    def __init__(self, value):
        self.instance_variable = value

    @classmethod
    def class_method(cls, x):
        cls.class_variable += x
        return cls.class_variable

# Creating instances of the class
obj1 = MyClass(5)
obj2 = MyClass(10)

# Calling the class method
print(MyClass.class_method(3))  # Output: 3
print(MyClass.class_method(7))  # Output: 10

Output
3
10

Static Method in Python: Static methods, as the name suggests, are not bound to either the class or its instances. 
They are defined using the @staticmethod decorator and do not take a reference to the instance or the class as their first 
parameter. Static methods are essentially regular functions within the class namespace and are useful for tasks that do not 
depend on instance-specific or class-specific data.

Syntax:
class C(object):
    @staticmethod
    def fun(arg1, arg2, ...):
        ...
returns: a static method for function fun.
In this example, the MathOperations class features static methods add and subtract for performing basic arithmetic operations. These methods can be directly invoked on the class without creating an instance, providing a convenient and state-independent way to perform mathematical operations.

Code:
class MathOperations:
    @staticmethod
    def add(x, y):
        return x + y

    @staticmethod
    def subtract(x, y):
        return x - y

# Using static methods without creating an instance
print(MathOperations.add(5, 3))        # Output: 8
print(MathOperations.subtract(10, 4))  # Output: 6

Output
8
6

Instance Method in Python: Instance methods are the most common type of methods in Python classes. They are associated with 
instances of a class and operate on the instance's data. When defining an instance method, the method's first parameter is
typically named self, which refers to the instance calling the method. This allows the method to access and manipulate the 
instance's attributes.

Syntax:
class MyClass:
   def instance_method(self, arg1, arg2, ...):
       # Instance method logic here
       pass
In this example, the Person class defines an instance method introduce which returns a formatted introduction based on the instance's name and age attributes. The instance person1 is created with the name "Kishan" and age 20, and invoking the introduce method prints a personalized introduction for that instance. Note that there's a small typo in the comment mentioning the age; it should be 20 instead of 30.

Code:
class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age

    def introduce(self):
        return f"Hi, I'm {self.name} and I'm {self.age} years old."


# Creating an instance of the class
person1 = Person("Kishan", 20)

# Calling the instance method
print(person1.introduce())  # Output: Hi, I'm Kishan and I'm 30 years old.

Output
Hi, I'm Kishan and I'm 20 years old.

Python Class Method Vs. Static Method Vs. Instance Method
Definition:  
Class Method: A method bound to the class itself, defined with "@classmethod"
Static Method: A method that does not receive an implicit first argument ('self' or 'cls'), defined with "@staticmethod"
Instance Method: A method defined within a class, taking `self` as the first parameter, representing the instance.

Access
Class Method: Can access class attributes and modify them.
Static Method: Cannot access or modify class or instance attributes.
Instance Method: Can access and modify instance attributes.

First Argument
Class Method: Receives 'cls' as the first argument representing the class.
Static Method: No implicit first argument is passed to the method.
Instance Method: Receives `self` as the first argument representing the instance.

Usage
Class Method: Often used for operations that modify or interact with class-level data.
Static Method: Typically used for utility functions that don't depend on instance or class state.
Instance Method: Commonly used for operations specific to individual instances.

Inheritance
Class Method: Can be overridden in subclasses, with 'cls' referring to the subclass.
Static Method: Can be called directly via the class or subclass, but not overridden.
Instance Method: Can be overridden in subclasses, with 'self' referring to the subclass instance.

Access Modifier
Class Method: Typically used when the method needs access to class-level data.
Static Method: Suitable when the method doesn't rely on instance or class attributes.
Instance Method: Preferred when the method operates on instance-specific attributes.

Example Use
Class Method: Calculating statistics across all instances of a class.
Static Method: Formatting dates, performing mathematical operations.
Instance Method: Returning information specific to an instance, like its attributes.

Usefulness
Class Method: Useful when dealing with class-level functionality and shared attributes.
Static Method: Handy for standalone functions related to the class but not dependent on its state.
Instance Method: Essential for modifying and accessing instance attributes and behaviors.

-------------------------------------------------------------------------------------------------
class Student:
    # class variables
    school_name = 'ABC School'

    # constructor
    def __init__(self, name, age):
        # instance variables
        self.name = name
        self.age = age

    # instance variables
    def show(self):
        print(self.name, self.age, Student.school_name)
        self.__class__.change_School("ABCD......")

    @classmethod
    def change_School(cls, name):
        cls.school_name = name

    @staticmethod
    def find_notes(subject_name):
        return ['chapter 1', 'chapter 2', 'chapter 3']


if __name__=='__main__':
    # create object
    obj = Student('Jessa', 12)
    # call instance method
    obj.show()

    # call class method using the class
    Student.change_School('XYZ School')
    # call class method using the object
    obj.change_School('PQR School')

    # call static method using the class
    Student.find_notes('Math')
    # call class method using the object
    obj.find_notes('Math')
