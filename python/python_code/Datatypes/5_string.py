Creating Strings
# Single quotes
string1 = 'Hello, world!'

# Double quotes
string2 = "Python is fun!"

# Triple quotes for multiline strings
string3 = """This is a
multiline string."""

Basic String Operations
# Concatenation
combined = string1 + " " + string2

# Repetition
repeated = string1 * 3

# Length
length = len(string1)

# Accessing characters
first_char = string1[0]
last_char = string1[-1]

# Slicing
substring = string1[0:5]
String Methods

# Changing case
upper_case = string1.upper()
lower_case = string1.lower()

# Splitting and joining
words = string2.split()  # Splits into a list of words
joined = " ".join(words)  # Joins list into a string

# Stripping whitespace
trimmed = "  Hello  ".strip()

# Replace
replaced = string1.replace("world", "Python")

# Finding substrings
index = string1.find("world")  # Returns -1 if not found

# Checking content
is_alpha = "abc".isalpha()
is_digit = "123".isdigit()
String Formatting

# f-strings (Python 3.6+)
name = "Alice"
formatted = f"Hello, {name}!"

# format() method
formatted = "Hello, {}!".format(name)

# Old-style formatting
formatted = "Hello, %s!" % name
Escape Characters

# Newline and tab
new_line = "Hello\nWorld"
tabbed = "Hello\tWorld"

# Escape quotes
quote = "She said, \"Python is awesome!\""


Strings are immutable in Python, so methods that modify a string return a new string.
Use r"raw strings" to avoid escaping backslashes in paths or regex patterns.
