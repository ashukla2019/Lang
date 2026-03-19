# Inheritance
# Inheritance is the ability of any class to extract and use features of other classes. It is the process by which new classes called the derived classes are created from existing classes called Base classes.
# A Python program to demonstrate inheritance  
   
 
class Person(): 
       
    # Constructor 
    def __init__(self, name): 
        self.name = name 
   
    # To get name 
    def getName(self): 
        return self.name 
   
    # To check if this person is employee 
    def isEmployee(self): 
        return False
   
   
# Inherited or Sub class (Note Person in bracket) 
class Employee(Person): 
   
    # Here we return true 
    def isEmployee(self): 
        return True
   
# Driver code 
emp = Person("Geek1")  # An Object of Person 
print(emp.getName(), emp.isEmployee()) 
   
emp = Employee("Geek2") # An Object of Employee 
print(emp.getName(), emp.isEmployee())

'''
Output:

Geek1 False
Geek2 True
'''
