
# Python program to demonstrate
# functions
 
1. Direct Function Call
The most common way to call a function.
        def greet():
                    print("Hello!")

        greet()  # Output: Hello!

2. Function Call with Arguments: Functions can accept arguments and return values.
        def add(a, b):
                    return a + b

        result = add(5, 3)  # result = 8
        print(result)

3. Using Default Arguments: If arguments are not provided, the default values are used.
        def greet(name="Guest"):
                    print(f"Hello, {name}!")
        greet()           # Output: Hello, Guest!
        greet("Alice")    # Output: Hello, Alice!

4. Using Keyword Arguments: You can specify arguments by name, in any order.
        def introduce(name, age):
                    print(f"My name is {name} and I'm {age} years old.")
        introduce(age=25, name="Bob")  # Output: My name is Bob and I'm 25 years old.

5. Passing Arbitrary Arguments: For unknown or variable numbers of arguments, use *args or **kwargs.
        def display(*args, **kwargs):
                    print("Positional arguments:", args)
                    print("Keyword arguments:", kwargs)

        display(1, 2, 3, name="Alice", age=25)
        # Output:
        # Positional arguments: (1, 2, 3)
        # Keyword arguments: {'name': 'Alice', 'age': 25}
                                                                                             
6. Calling Functions Dynamically: Using a reference to the function.
        def greet():
                    print("Hello!")

        func = greet  # Assign function to a variable
        func()        # Output: Hello!
            
7. Calling Functions from a Dictionary: Functions can be stored in dictionaries and called dynamically.
        def add(a, b):
                    return a + b

        def subtract(a, b):
            return a - b

        operations = {
            "add": add,
            "subtract": subtract
        }

        result = operations["add"](10, 5)  # result = 15
        print(result)
--------------------------------

What is Python main function?
The Python main function refers to the entry point of a Python program. 
It is often defined using the if __name__ == "__main__": construct to ensure that certain code
is only executed when the script is run directly, not when it is imported as a module.





