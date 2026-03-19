In Python, a tuple is an immutable, ordered collection of items. Tuples are similar to lists, but once a tuple is created, 
its contents cannot be changed (i.e., no adding, removing, or modifying elements). Tuples are commonly used when you want to represent a fixed collection of items that should not be altered.

1) Creating a Tuple
Using parentheses:
my_tuple = (1, 2, 3)

Without parentheses (optional):
my_tuple = 1, 2, 3

Empty tuple:
empty_tuple = ()

Single-element tuple: Add a trailing comma to differentiate it from a simple parenthesized expression:
single_element_tuple = (1,)

Accessing Tuple Elements
Tuples are indexed starting at 0:
my_tuple = (10, 20, 30)
print(my_tuple[0])  # Output: 10
print(my_tuple[-1])  # Output: 30 (last element)

Common Operations
Length of a tuple:
len(my_tuple)  # Output: 3

Slicing:
sub_tuple = my_tuple[0:2]  # Output: (10, 20)

Concatenation:
new_tuple = my_tuple + (40, 50)  # Output: (10, 20, 30, 40, 50)

Repetition:
repeated_tuple = my_tuple * 2  # Output: (10, 20, 30, 10, 20, 30)

Iterating Over a Tuple
for item in my_tuple:
    print(item)
Tuple Unpacking
You can assign the values of a tuple to multiple variables:
a, b, c = my_tuple
print(a, b, c)  # Output: 10 20 30

Why Use Tuples?
Immutability: Tuples are immutable, so they are more secure than lists in certain scenarios (e.g., keys in dictionaries).
Performance: Tuples are generally faster than lists.
Fixed structure: Tuples are suitable for representing fixed data structures like geographic coordinates or RGB colors.
Methods Available for Tuples
Tuples have only two methods because they are immutable:

count(): Returns the number of times a value appears in the tuple.
my_tuple = (1, 2, 3, 1)
print(my_tuple.count(1))  # Output: 2
index(): Returns the index of the first occurrence of a value.

print(my_tuple.index(2))  # Output: 1
