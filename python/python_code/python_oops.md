# Python OOPs — Complete Interview Notes

## 1. What is OOP?

Object-Oriented Programming (OOP) is a programming paradigm where programs are organized around **objects** that contain:

* Data → attributes
* Behavior → methods

The four major OOP concepts are:

1. Encapsulation
2. Abstraction
3. Inheritance
4. Polymorphism

---

# 2. Class and Object

A **class** is a blueprint.

An **object** is an instance of a class.

```python
class Car:
    def __init__(self, brand, model):
        self.brand = brand
        self.model = model

    def display(self):
        print(self.brand, self.model)


car1 = Car("Toyota", "Camry")
car2 = Car("Honda", "City")

car1.display()
car2.display()
```

### Key points

```text
Car      -> Class
car1     -> Object
car2     -> Object
brand    -> Instance variable
model    -> Instance variable
display  -> Instance method
```

---

# 3. `self`

`self` refers to the **current object**.

```python
class Student:
    def __init__(self, name):
        self.name = name

    def display(self):
        print(self.name)


s = Student("John")

s.display()
```

Conceptually:

```text
s.display()
      |
      v
display(s)
```

Python explicitly passes the object as the first argument to an instance method.

### Important

`self` is **not a Python keyword**.

It is the conventional name used for the current object reference.

You could technically write:

```python
class Test:
    def show(current):
        print(current)
```

But `self` should always be preferred.

---

# 4. Constructor / `__init__()`

Python uses `__init__()` to initialize an object after it is created.

```python
class Student:
    def __init__(self, name, age):
        self.name = name
        self.age = age


s = Student("John", 25)

print(s.name)
print(s.age)
```

Output:

```text
John
25
```

### Important distinction

In Python, `__init__()` is technically an **initializer**, not the actual object allocator.

Object creation involves `__new__()` first, followed by `__init__()`.

For normal interview-level Python code, `__init__()` is commonly referred to as the constructor.

---

# 5. Instance Variables

Instance variables belong to individual objects.

```python
class Employee:
    def __init__(self, name, salary):
        self.name = name
        self.salary = salary


e1 = Employee("Alice", 50000)
e2 = Employee("Bob", 60000)

print(e1.name)
print(e2.name)

print(e1.salary)
print(e2.salary)
```

Each object has its own:

```text
name
salary
```

Conceptually:

```text
e1
 |
 +-- name = Alice
 +-- salary = 50000


e2
 |
 +-- name = Bob
 +-- salary = 60000
```

---

# 6. Class Variables

A class variable is shared by objects unless an instance overrides it.

```python
class Employee:
    company = "Google"

    def __init__(self, name):
        self.name = name


e1 = Employee("Alice")
e2 = Employee("Bob")

print(e1.company)
print(e2.company)

print(Employee.company)
```

Output:

```text
Google
Google
Google
```

Changing the class variable:

```python
Employee.company = "Microsoft"

print(e1.company)
print(e2.company)
```

Output:

```text
Microsoft
Microsoft
```

---

# 7. Instance Method

An instance method receives `self`.

```python
class Calculator:
    def add(self, a, b):
        return a + b


c = Calculator()

print(c.add(10, 20))
```

Output:

```text
30
```

---

# 8. Class Method

A class method uses `cls`.

It is declared using:

```python
@classmethod
```

Example:

```python
class Employee:
    company = "Google"

    @classmethod
    def change_company(cls, name):
        cls.company = name


Employee.change_company("Microsoft")

print(Employee.company)
```

Output:

```text
Microsoft
```

### `self` vs `cls`

```text
self -> current object
cls  -> current class
```

---

# 9. Static Method

A static method does not automatically receive `self` or `cls`.

Use:

```python
@staticmethod
```

Example:

```python
class Calculator:

    @staticmethod
    def add(a, b):
        return a + b


print(Calculator.add(10, 20))
```

A static method is useful when the function logically belongs to the class but does not need object or class state.

---

# 10. Encapsulation

Encapsulation means bundling data and methods together and controlling how the data is accessed.

Example:

```python
class BankAccount:
    def __init__(self, balance):
        self._balance = balance

    def deposit(self, amount):
        self._balance += amount

    def get_balance(self):
        return self._balance


account = BankAccount(1000)

account.deposit(500)

print(account.get_balance())
```

---

# 11. Protected Convention — `_variable`

Python does not have a strict `protected` keyword.

A single underscore is a convention:

```python
self._balance
```

It means:

> This is intended for internal/protected use.

Example:

```python
class Employee:
    def __init__(self, salary):
        self._salary = salary
```

It can still technically be accessed:

```python
e = Employee(50000)

print(e._salary)
```

So `_salary` is **not truly private**.

---

# 12. Private Members — `__variable`

Python uses double underscore for name mangling.

```python
class BankAccount:
    def __init__(self, balance):
        self.__balance = balance

    def get_balance(self):
        return self.__balance


account = BankAccount(1000)

print(account.get_balance())
```

Normally:

```python
print(account.__balance)
```

does not work.

Python internally transforms the name approximately to:

```text
_BankAccount__balance
```

This mechanism is called **name mangling**.

---

# 13. Inheritance

Inheritance allows a child class to reuse and extend a parent class.

```python
class Animal:
    def eat(self):
        print("Eating")


class Dog(Animal):
    def bark(self):
        print("Barking")


dog = Dog()

dog.eat()
dog.bark()
```

Output:

```text
Eating
Barking
```

Relationship:

```text
Dog IS-A Animal
```

---

# 14. Method Overriding

A child class can provide its own implementation of a parent method.

```python
class Animal:
    def sound(self):
        print("Animal sound")


class Dog(Animal):
    def sound(self):
        print("Bark")


dog = Dog()

dog.sound()
```

Output:

```text
Bark
```

This is **method overriding**.

---

# 15. `super()`

`super()` is used to access parent-class functionality.

```python
class Animal:
    def __init__(self, name):
        self.name = name

    def display(self):
        print(self.name)


class Dog(Animal):
    def __init__(self, name, breed):
        super().__init__(name)
        self.breed = breed


dog = Dog("Tommy", "Labrador")

dog.display()
print(dog.breed)
```

Here:

```python
super().__init__(name)
```

calls:

```python
Animal.__init__(...)
```

through Python's method-resolution mechanism.

---

# 16. Polymorphism

Polymorphism means the same interface can have different implementations.

```python
class Dog:
    def sound(self):
        print("Bark")


class Cat:
    def sound(self):
        print("Meow")


def make_sound(animal):
    animal.sound()


make_sound(Dog())
make_sound(Cat())
```

Output:

```text
Bark
Meow
```

The function doesn't need to know whether the object is a `Dog` or `Cat`.

---

# 17. Duck Typing

Python heavily uses **duck typing**.

The idea is:

> If an object behaves like the required type, Python can use it.

```python
class Dog:
    def sound(self):
        print("Bark")


class Robot:
    def sound(self):
        print("Beep")


def make_sound(obj):
    obj.sound()


make_sound(Dog())
make_sound(Robot())
```

There is no inheritance relationship between `Dog` and `Robot`.

Both work because both provide:

```python
sound()
```

---

# 18. Abstraction

Abstraction means exposing essential behavior while hiding implementation details.

Python provides abstract classes through the `abc` module.

```python
from abc import ABC, abstractmethod


class Animal(ABC):

    @abstractmethod
    def sound(self):
        pass


class Dog(Animal):

    def sound(self):
        print("Bark")


dog = Dog()

dog.sound()
```

You cannot normally instantiate:

```python
Animal()
```

because `Animal` has an abstract method.

---

# 19. Abstract Class with Multiple Methods

```python
from abc import ABC, abstractmethod


class Shape(ABC):

    @abstractmethod
    def area(self):
        pass

    @abstractmethod
    def perimeter(self):
        pass


class Rectangle(Shape):

    def __init__(self, length, width):
        self.length = length
        self.width = width

    def area(self):
        return self.length * self.width

    def perimeter(self):
        return 2 * (self.length + self.width)


r = Rectangle(10, 5)

print(r.area())
print(r.perimeter())
```

---

# 20. Multiple Inheritance

Python supports multiple inheritance.

```python
class Father:
    def skills(self):
        print("Driving")


class Mother:
    def hobbies(self):
        print("Painting")


class Child(Father, Mother):
    pass


c = Child()

c.skills()
c.hobbies()
```

Relationship:

```text
       Father       Mother
          \           /
           \         /
             Child
```

---

# 21. Method Resolution Order — MRO

When multiple inheritance exists, Python uses **MRO** to determine the order in which classes are searched for methods.

```python
class A:
    def show(self):
        print("A")


class B(A):
    def show(self):
        print("B")


class C(A):
    def show(self):
        print("C")


class D(B, C):
    pass


d = D()

d.show()

print(D.mro())
```

MRO is approximately:

```text
D -> B -> C -> A -> object
```

You can inspect it using:

```python
print(D.mro())
```

or:

```python
print(D.__mro__)
```

---

# 22. Property

`@property` allows a method to be accessed like an attribute.

```python
class Employee:
    def __init__(self, salary):
        self._salary = salary

    @property
    def salary(self):
        return self._salary

    @salary.setter
    def salary(self, value):
        if value < 0:
            raise ValueError("Salary cannot be negative")

        self._salary = value


e = Employee(50000)

print(e.salary)

e.salary = 60000

print(e.salary)
```

The caller uses:

```python
e.salary
```

instead of:

```python
e.salary()
```

---

# 23. Magic / Dunder Methods

Python provides special methods surrounded by double underscores.

Examples:

```text
__init__
__str__
__len__
__eq__
__add__
__lt__
```

These are commonly called **dunder methods**.

---

# 24. `__str__()`

Controls the user-friendly string representation of an object.

```python
class Student:
    def __init__(self, name):
        self.name = name

    def __str__(self):
        return f"Student: {self.name}"


s = Student("John")

print(s)
```

Output:

```text
Student: John
```

---

# 25. Operator Overloading

Python allows operators to be customized using dunder methods.

Example:

```python
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __add__(self, other):
        return Point(
            self.x + other.x,
            self.y + other.y
        )

    def __str__(self):
        return f"({self.x}, {self.y})"


p1 = Point(10, 20)
p2 = Point(30, 40)

p3 = p1 + p2

print(p3)
```

Output:

```text
(40, 60)
```

Conceptually:

```python
p1 + p2
```

calls:

```python
p1.__add__(p2)
```

---

# 26. Equality Operator Overloading

```python
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y


p1 = Point(10, 20)
p2 = Point(10, 20)

print(p1 == p2)
```

Output:

```text
True
```

---

# 27. Composition

Composition means one class contains an object of another class.

Example:

```python
class Engine:
    def start(self):
        print("Engine started")


class Car:
    def __init__(self):
        self.engine = Engine()

    def start(self):
        self.engine.start()
        print("Car started")


car = Car()

car.start()
```

Relationship:

```text
Car HAS-A Engine
```

---

# 28. Inheritance vs Composition

## Inheritance

```text
Dog IS-A Animal
```

```python
class Dog(Animal):
    pass
```

Use inheritance when there is a genuine **IS-A** relationship.

## Composition

```text
Car HAS-A Engine
```

```python
class Car:
    def __init__(self):
        self.engine = Engine()
```

Use composition when one object is built using another object.

### Interview rule

Prefer **composition over inheritance** when inheritance does not represent a natural IS-A relationship.

---

# 29. Complete OOP Example

The following example combines:

* Encapsulation
* Abstraction
* Inheritance
* Polymorphism
* Composition

```python
from abc import ABC, abstractmethod


class Engine:
    def start(self):
        print("Engine started")


class Vehicle(ABC):

    def __init__(self, brand):
        self._brand = brand

    @abstractmethod
    def move(self):
        pass

    def get_brand(self):
        return self._brand


class Car(Vehicle):

    def __init__(self, brand):
        super().__init__(brand)
        self.engine = Engine()

    def move(self):
        self.engine.start()
        print(f"{self._brand} car is moving")


class Bike(Vehicle):

    def move(self):
        print(f"{self._brand} bike is moving")


def start_vehicle(vehicle):
    vehicle.move()


car = Car("Toyota")
bike = Bike("Honda")

start_vehicle(car)
start_vehicle(bike)
```

This demonstrates:

```text
Abstraction:
    Vehicle

Inheritance:
    Car -> Vehicle
    Bike -> Vehicle

Encapsulation:
    _brand

Composition:
    Car HAS-A Engine

Polymorphism:
    car.move()
    bike.move()
```

---

# 30. Four Pillars of OOP

## 30.1 Encapsulation

Bundle data and behavior together and control access.

```python
class BankAccount:
    def __init__(self, balance):
        self.__balance = balance

    def deposit(self, amount):
        self.__balance += amount
```

---

## 30.2 Abstraction

Hide implementation details and expose required operations.

```python
from abc import ABC, abstractmethod


class Shape(ABC):

    @abstractmethod
    def area(self):
        pass
```

---

## 30.3 Inheritance

Reuse and extend an existing class.

```python
class Animal:
    def eat(self):
        print("Eating")


class Dog(Animal):
    pass
```

---

## 30.4 Polymorphism

Same interface, different behavior.

```python
class Dog:
    def sound(self):
        print("Bark")


class Cat:
    def sound(self):
        print("Meow")


def sound(animal):
    animal.sound()
```

---

# 31. Important Python OOP Differences from C++

For a C++ developer learning Python, remember these differences.

| Concept              | C++                                         | Python                                            |
| -------------------- | ------------------------------------------- | ------------------------------------------------- |
| Current object       | `this`                                      | `self`                                            |
| Constructor          | `ClassName()`                               | `__init__()`                                      |
| Destructor           | `~ClassName()`                              | `__del__()`                                       |
| Private              | `private`                                   | `__name` name mangling                            |
| Protected            | `protected`                                 | `_name` convention                                |
| Public               | `public`                                    | Normal attribute/method                           |
| Class method         | `static`/member functions depending on need | `@classmethod`                                    |
| Static method        | `static`                                    | `@staticmethod`                                   |
| Abstract class       | Pure virtual functions                      | `ABC` + `@abstractmethod`                         |
| Operator overloading | `operator+`                                 | `__add__`                                         |
| Multiple inheritance | Supported                                   | Supported                                         |
| Interfaces           | Abstract classes/interfaces patterns        | ABC / protocols                                   |
| Method overloading   | Supported                                   | No traditional signature-based overloading        |
| Duck typing          | Not typical                                 | Very common                                       |
| Memory management    | Manual/RAII + smart pointers                | Automatic reference counting + garbage collection |

---

# 32. Python Method Overloading

Python does **not** support traditional C++-style method overloading based on parameter lists.

This does not work as traditional overloading:

```python
class Calculator:

    def add(self, a):
        return a

    def add(self, a, b):
        return a + b
```

The second `add()` replaces the first one.

Instead, use default arguments:

```python
class Calculator:

    def add(self, a, b=0):
        return a + b


c = Calculator()

print(c.add(10))
print(c.add(10, 20))
```

Output:

```text
10
30
```

Or use `*args`:

```python
class Calculator:

    def add(self, *args):
        return sum(args)


c = Calculator()

print(c.add(10))
print(c.add(10, 20))
print(c.add(10, 20, 30))
```

---

# 33. Destructor — `__del__()`

Python provides:

```python
__del__()
```

which may be called when an object is being finalized.

```python
class Test:

    def __del__(self):
        print("Object destroyed")


obj = Test()

del obj
```

### Important interview point

Do not treat `__del__()` as an exact equivalent of a C++ destructor.

Python's object lifetime and garbage collection behavior are different, and `__del__()` should generally not be relied upon for deterministic resource management.

For files, locks, sockets, etc., prefer context managers:

```python
with open("file.txt") as f:
    data = f.read()
```

---

# 34. `object` — Base Class

Python classes ultimately derive from `object` in normal Python 3 class semantics.

```python
class Student:
    pass
```

is effectively based on:

```python
class Student(object):
    pass
```

You can see inheritance through:

```python
print(Student.mro())
```

---

# 35. `isinstance()` and `issubclass()`

## `isinstance()`

Checks whether an object is an instance of a class.

```python
class Animal:
    pass


class Dog(Animal):
    pass


dog = Dog()

print(isinstance(dog, Dog))
print(isinstance(dog, Animal))
```

Both are:

```text
True
```

because `Dog` inherits from `Animal`.

## `issubclass()`

Checks class inheritance.

```python
print(issubclass(Dog, Animal))
```

Output:

```text
True
```

---

# 36. Important OOP Interview Questions

### Q1. What are the four pillars of OOP?

```text
Encapsulation
Abstraction
Inheritance
Polymorphism
```

### Q2. What is `self`?

`self` refers to the current object.

### Q3. What is `cls`?

`cls` refers to the current class and is used with class methods.

### Q4. Difference between `_x` and `__x`?

```text
_x  -> convention for internal/protected use
__x -> name mangling
```

Neither provides C++-style strict private/protected access.

### Q5. Difference between instance and class variables?

```text
Instance variable -> belongs to an object
Class variable    -> belongs to the class/shared by instances
```

### Q6. What is `super()`?

Used to access parent-class functionality through Python's MRO.

### Q7. What is duck typing?

Python focuses on whether an object supports the required behavior rather than requiring a specific declared type.

### Q8. Does Python support multiple inheritance?

Yes.

```python
class C(A, B):
    pass
```

### Q9. Does Python support method overloading?

Not traditional C++-style signature-based overloading.

Use:

```text
default arguments
*args
**kwargs
```

### Q10. What is MRO?

**Method Resolution Order** determines the order in which Python searches classes for attributes and methods.

```python
ClassName.mro()
```

### Q11. What is composition?

A HAS-A relationship.

```text
Car HAS-A Engine
```

### Q12. What is inheritance?

An IS-A relationship.

```text
Dog IS-A Animal
```

---

# 37. Final Python OOP Cheat Sheet

```text
CLASS
    class MyClass:
        pass

OBJECT
    obj = MyClass()

INITIALIZER
    __init__()

CURRENT OBJECT
    self

CURRENT CLASS
    cls

INSTANCE VARIABLE
    self.x

CLASS VARIABLE
    ClassName.x

INSTANCE METHOD
    def method(self):

CLASS METHOD
    @classmethod
    def method(cls):

STATIC METHOD
    @staticmethod
    def method():

ENCAPSULATION
    _x
    __x

INHERITANCE
    class Child(Parent):

PARENT ACCESS
    super()

ABSTRACTION
    ABC
    @abstractmethod

POLYMORPHISM
    Same interface
    Different implementation

COMPOSITION
    HAS-A

MRO
    ClassName.mro()

PROPERTY
    @property

OPERATOR OVERLOADING
    __add__
    __eq__
    __lt__

STRING REPRESENTATION
    __str__

TYPE CHECKING
    isinstance()
    issubclass()
```

---

# 38. What to Memorize for Interviews

For a Python OOP interview, be comfortable writing these from memory:

```text
1. Class + object
2. __init__ + self
3. Instance vs class variables
4. Instance/class/static methods
5. Encapsulation
6. _x vs __x
7. Inheritance
8. Method overriding
9. super()
10. Multiple inheritance
11. MRO
12. Polymorphism
13. Duck typing
14. ABC + abstractmethod
15. Composition
16. @property
17. Dunder methods
18. Operator overloading
19. isinstance / issubclass
20. Method overloading limitations
```

For **C++ → Python interview preparation**, the highest-priority concepts are `self`, `__init__`, class vs instance variables, `@classmethod`, `@staticmethod`, inheritance, `super()`, MRO, duck typing, ABCs, properties, and dunder/operator-overloading methods.
