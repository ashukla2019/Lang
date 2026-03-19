
1. Iterating Over a List:
	fruits = ["apple", "banana", "cherry"]
		for fruit in fruits:
	    	print(fruit)
	Output:
	apple
	banana
	cherry
2. Iterating Over a String:
	word = "Python"
	for letter in word:
	    print(letter)
	Output:
	P
	y
	t
	h
	o
	n
3. Using range(): The range() function generates a sequence of numbers.
	for i in range(5):
	    print(i)
	Output:	
	0
	1
	2
	3
	4
	Example with start and end:
	for i in range(1, 6):
	    print(i)
	Output:		
	1
	2
	3
	4
	5

	Example with step:
	for i in range(0, 10, 2):
	    print(i)
	Output:
	0
	2
	4
	6
	8
4. Iterating Over a Dictionary:
	person = {"name": "Alice", "age": 25, "city": "New York"}
	for key, value in person.items():
	    print(f"{key}: {value}")
	Output:
	name: Alice
	age: 25
	city: New York
5. Nested For Loops:
	for i in range(3):
	    for j in range(2):
	        print(f"i={i}, j={j}")
	Output:
	i=0, j=0
	i=0, j=1
	i=1, j=0
	i=1, j=1
	i=2, j=0
	i=2, j=1
---------------------------------

#While Loops:
#This is used for executing set of statements within its block as long as the
#associated loop condition is evaluated to True as shown in the image below:

count = 5
while count > 0:
	print(count)
	count -= 1

output:
'''
5
4
3
2
1
'''
