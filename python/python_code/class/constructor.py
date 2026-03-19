# The self
# self represents the instance of the class. By using the self keyword 
# we can access the attributes and methods of the class in python. It binds the attributes with the given arguments.
# Note: For more information, refer self in Python class.
# Constructors and Destructor

# Constructors: Constructors are generally used for instantiating an object.
# The task of constructors is to initialize(assign values) to the data members of 
# the class when an object of class is created. In Python the __init__() method is called the constructor and is always called when an object is created. There can be two types of constructors:
# Default constructor: The constructor which is called implicilty and do not accept any argument.
# Parameterized constructor:Constructor which is called explicitly with parameters is known as parameterized constructor.

# Python program to demonstrate constructors
 
 
class Addition:
    # parameterized constructor 
    def __init__(self, f, s): 
        self.first = f 
        self.second = s
   
    def calculate(self):
        print(self.first + self.second)
   
# Invoking parameterized constructor
obj = Addition(1000, 2000) 
   
# perform Addition 
obj.calculate() 

'''
Output:

3000
'''
