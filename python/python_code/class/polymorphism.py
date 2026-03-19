# Polymorphism
# Polymorphism refers to the ability of OOPs programming languages to differentiate between 
# entities with the same name efficiently. This is done by Python with the help of the signature
# of these entities.
# Python program to demonstrate Polymorphism
  
class A():
    def show(self):
        print("Inside A")
         
class B():
    def show(self):
        print("Inside B")
         
# Driver's code
a = A()
a.show()
b = B()
b.show()

'''
Output:

Inside A
Inside B
'''