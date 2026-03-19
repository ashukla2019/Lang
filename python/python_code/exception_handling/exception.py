
What is Exception Handling in Python?
Exception handling lets you catch errors and prevent the program from crashing.

Python uses:
try
except
else
finally
raise

1. Basic try–except
try:
    x = 10 / 0
except ZeroDivisionError:
    print("You cannot divide by zero!")

Output:
You cannot divide by zero! 

---------------------------------

2. Multiple except blocks
try:
    num = int("abc")
except ValueError:
    print("Invalid number!")
except TypeError:
    print("Type error occurred!")

Output:
Invalid number!
------------------------------------

3. Catching all exceptions
try:
    print(10 / 0)
except Exception as e:
    print("Error:", e)
Output:
Error: division by zero

-----------------------------------
4. try–except–else
else runs only when no exception occurs.

try:
    num = int("50")
except ValueError:
    print("Conversion failed!")
else:
    print("Converted successfully:", num)
Output:
Converted successfully: 50

---------------------------------
5. try–finally
finally runs always, even if there is an error.

try:
    f = open("test.txt")
except FileNotFoundError:
    print("File not found!")
finally:
    print("This will always run.")
Output:
File not found!
This will always run.

-------------------------------
6. raise your own exception
age = 15

if age < 18:
    raise ValueError("Age must be 18 or above!")
Output:
ValueError: Age must be 18 or above!

-----------------------------
7. Custom Exception Class
class NegativeNumberError(Exception):
    pass

try:
    n = -5
    if n < 0:
        raise NegativeNumberError("Number cannot be negative!")
except NegativeNumberError as e:
    print("Custom Error:", e)
Output:
Custom Error: Number cannot be negative!