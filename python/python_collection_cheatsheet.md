# ================================
# PYTHON COLLECTIONS CHEAT SHEET
# ================================

##################################
# 1. LIST []
##################################

# Create
nums = [1, 2, 3]

# Add
nums.append(4)          # Add one item
nums.extend([5, 6])     # Add multiple items
nums.insert(1, 10)      # Insert at index

# Remove
nums.remove(10)         # Remove by value
nums.pop()              # Remove last item
nums.pop(1)             # Remove by index
del nums[0]             # Delete by index
nums.clear()            # Remove all items

# Search
2 in nums
nums.index(2)
nums.count(2)

# Sort
nums.sort()
nums.sort(reverse=True)
sorted(nums)

# Reverse
nums.reverse()

# Copy
copy = nums.copy()

# Other
len(nums)
max(nums)
min(nums)
sum(nums)


##################################
# 2. TUPLE ()
##################################

# Create
t = (1, 2, 3)

# Access
t[0]
t[-1]

# Count & Index
t.count(2)
t.index(3)

# Packing
person = ("John", 25)

# Unpacking
name, age = person

# Single element tuple
single = (10,)

# Convert
list(t)
tuple([1, 2, 3])


##################################
# 3. SET {}
##################################

# Create
s = {1, 2, 3}

# Add
s.add(4)
s.update([5, 6])

# Remove
s.remove(2)      # Error if missing
s.discard(2)     # No error
s.pop()          # Removes random item
s.clear()

# Membership
3 in s

# Set Operations
a = {1,2,3}
b = {3,4,5}

a | b            # Union
a & b            # Intersection
a - b            # Difference
a ^ b            # Symmetric Difference

# Subset/Superset
a.issubset(b)
a.issuperset(b)

# Copy
copy = s.copy()


##################################
# 4. DICTIONARY {} (Map)
##################################

# Create
student = {
    "name": "John",
    "age": 25
}

# Read
student["name"]
student.get("age")

# Add/Update
student["city"] = "Pune"
student.update({"age": 26})

# Remove
student.pop("age")
student.popitem()
del student["name"]
student.clear()

# Keys/Values
student.keys()
student.values()
student.items()

# Check
"name" in student

# Copy
copy = student.copy()

# Iterate
for key in student:
    print(key)

for key, value in student.items():
    print(key, value)


##################################
# 5. STRING (Bonus)
##################################

text = "python"

text.upper()
text.lower()
text.title()
text.capitalize()

text.replace("py", "Py")
text.split("t")
"-".join(["a","b","c"])

text.startswith("py")
text.endswith("on")

text.find("th")
text.count("o")

len(text)


##################################
# 6. Useful Built-ins
##################################

len(obj)
type(obj)
sorted(obj)
reversed(obj)

enumerate(list)
zip(list1, list2)

any(list)
all(list)

sum(list)
max(list)
min(list)


##################################
# 7. List Comprehension
##################################

nums = [x*x for x in range(5)]

evens = [x for x in range(10) if x % 2 == 0]


##################################
# 8. Dictionary Comprehension
##################################

square = {x: x*x for x in range(5)}


##################################
# 9. Set Comprehension
##################################

unique = {x*x for x in range(5)}


##################################
# 10. Generator Expression
##################################

gen = (x*x for x in range(5))


=================================
MEMORY TRICK
=================================

LIST []      -> Ordered + Mutable + Duplicates
               append(), extend(), insert()
               remove(), pop(), sort()

TUPLE ()     -> Ordered + Immutable
               count(), index()

SET {}       -> Unordered + Unique
               add(), remove(), union(|), intersection(&)

DICT {}      -> Key : Value
               get(), keys(), values(), items(), update()

=================================
MOST ASKED INTERVIEW METHODS
=================================

List :
append()
extend()
insert()
remove()
pop()
sort()
reverse()
copy()

Tuple :
count()
index()

Set :
add()
update()
remove()
discard()
union
intersection
difference

Dictionary :
get()
update()
keys()
values()
items()
pop()
popitem()
