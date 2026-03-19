List Characteristics
Ordered - They maintain the order of elements.
Mutable - Items can be changed after creation.
Allow duplicates - They can contain duplicate values.
-----------------------------------------------------------------------------------------
Python lists can be used to implement CRUD (Create, Read, Update, Delete) operations effectively.
Here's a breakdown of how each operation works in the context of lists:

1. Create: Adding Elements to a List
Creating or adding elements to a list can be done using methods like append(), extend(), or insert().

# Create an empty list
my_list = []

# a list of three elements
ages = [19, 26, 29]
print(ages)
# Output: [19, 26, 29]

#List Items of Different Types: a list containing strings and numbers
student = ['Jack', 32, 'Computer Science']
print(student)

#Using list() to Create Lists: We can use the built-in list() function to convert other iterables (strings, dictionaries, tuples, etc.) to a list.
x = "axz"

# convert to list
result = list(x)

print(result)  # ['a', 'x', 'z']
----------------------------------------------------------------------------------------------
2. Read: Accessing Elements in a List
Each element in a list is associated with a number, known as an index.
The index of first item is 0, the index of second item is 1, and so on.

Reading elements can be done using indexing, slicing, or iteration.

# List for demonstration
my_list = [10, 20, 30, 40, 50]

# Access element by index
print(my_list[0])            # Output: 10 (first element)
print(my_list[-1])           # Output: 50 (last element)

# Iterate through the list
for item in my_list:
    print(item)
# Output:
# 10
# 20
# 30
# 40
# 50

#Negative Indexing in Python: Python also supports negative indexing. The index of the last element is -1, the second-last 
element is -2, and so on.
languages = ['Python', 'Swift', 'C++']

# Access item at index 0
print(languages[-1])   # C++

# Access item at index 2
print(languages[-3])   # Python

#Slicing of a List in Python: In Python, it is possible to access a section of items from the list using the slicing operator :
my_list = ['p', 'r', 'o', 'g', 'r', 'a', 'm']

# items from index 2 to index 4
print(my_list[2:5])

# items from index 5 to end
print(my_list[5:])

# items beginning to end
print(my_list[:])
----------------------------------------------------------------------------------------
3. Update: Modifying Elements in a List
Updating elements involves changing specific elements by their index or updating multiple elements using slicing.

# using append method 
fruits = ['apple', 'banana', 'orange']
fruits.append('cherry')

print('Updated List:', fruits)
Output:
Updated List: ['apple', 'banana', 'orange', 'cherry']

#The insert() method adds an element at the specified index. For example,
fruits = ['apple', 'banana', 'orange']
print("Original List:", fruits) 

# insert 'cherry' at index 2
fruits.insert(2, 'cherry')

print("Updated List:", fruits)

Output:
Original List: ['apple', 'banana', 'orange']
Updated List: ['apple', 'banana', 'cherry', 'orange']

#Add Elements to a List From Other Iterables: We use the extend() method to add elements to a list from other iterables. For example,

numbers = [1, 3, 5]
print('Numbers:', numbers)

even_numbers  = [2, 4, 6]

# adding elements of one list to another
numbers.extend(even_numbers)

print('Updated Numbers:', numbers) 

#Output
Numbers: [1, 3, 5]
Updated Numbers: [1, 3, 5, 2, 4, 6]

#Change List Items
We can change the items of a list by assigning new values using the = operator. For example,

colors = ['Red', 'Black', 'Green']
print('Original List:', colors)

# changing the third item to 'Blue'
colors[2] = 'Blue'

print('Updated List:', colors)
Run Code
Output

Original List: ['Red', 'Black', 'Green']
Updated List: ['Red', 'Black', 'Blue']
Here, we have replaced the element at index 2: 'Green' with 'Blue'.

-------------------------------------------------------------------------------------
4. Delete: Removing Elements from a List
Deleting elements can be done using del, remove(), pop(), or slicing.

# List for demonstration
my_list = [10, 20, 30, 40, 50]

# Remove by index using del
del my_list[2]             # Removes the element at index 2
print(my_list)             # Output: [10, 20, 40, 50]

# Remove by value using remove()
my_list.remove(20)         # Removes the first occurrence of 20
print(my_list)             # Output: [10, 40, 50]

# Remove the last element using pop()
last_element = my_list.pop()  # Pops and returns the last element
print(last_element)           # Output: 50
print(my_list)                # Output: [10, 40]

# Remove multiple elements using slicing
my_list = [10, 20, 30, 40, 50]
my_list[1:4] = []           # Removes elements at index 1 to 3
print(my_list)              # Output: [10, 50]

# Clear the entire list
my_list.clear()             # Empties the list
print(my_list)              # Output: []

------------------------------------------------------------------------------------------
class mylist():
    def __init__(self):
        #Empty list
        self.mylist = []

    def create_list(self):
        # list with different types of data
        self.mylist = [1, 2, "hello"]

    def read_list(self):
        # Access single character
        print(self.mylist[0])

        # Access characters in range: slicing
        print(self.mylist[:len(self.mylist) - 2])

        # Iterate list using for loop:
        for item in self.mylist:
            print(item)

    def update_list(self):
        #Add single elements: append()
        self.mylist.append(4)

        # Add multiple elements: extend()
        self.mylist.extend([5, "bye"])

        #insert element at particular index:
        self.mylist.insert(2, "hi")


    def delete_list(self):
        #Remove element by value:
        self.mylist.remove("bye")

        #Remove the last element using pop()
        self.mylist.pop()

        # Remove by index using del
        del self.mylist[2]

        # Clear the entire list
        self.mylist.clear()

    def __del__(self):
        if self.mylist:
            del self.mylist

if __name__ == '__main__':
    lt = mylist()
    lt.create_list()
    lt.read_list()
    lt.update_list()
    lt.read_list()
    lt.delete_list()
    
