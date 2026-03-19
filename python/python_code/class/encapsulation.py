# Encapsulation
# Encapsulation describes the idea of wrapping data and the methods that work on data within one unit. This puts restrictions on accessing variables and methods directly and can prevent the accidental modification of data.
# Python program to demonstrate encapsulation 
   
# Creating a Base class 
class Base: 
    def __init__(self): 
        self.a = "GeeksforGeeks"
        self.__c = "GeeksforGeeks"
   
# Creating a derived class 
class Derived(Base): 
    def __init__(self): 
           
        # Calling constructor of 
        # Base class
        Base.__init__(self)  
        print("Calling private member of base class: ") 
        print(self.__a) 
# Driver code 
#obj = Derived()

'''
Output:

Traceback (most recent call last):
  File "/home/5a605c59b5b88751d2b93dd5f932dbd5.py", line 20, in 
    obj = Derived()
  File "/home/5a605c59b5b88751d2b93dd5f932dbd5.py", line 18, in __init__
    print(self.__a) 
AttributeError: 'Derived' object has no attribute '_Derived__a'
'''
