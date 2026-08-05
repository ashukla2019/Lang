# Python Collections Cheat Sheet

A quick reference for Python's built-in collection types and commonly used methods.

---

## 1. List `[]`

### Create

```python
nums = [1, 2, 3]
```

### Add Elements

```python
nums.append(4)          # Add one item
nums.extend([5, 6])     # Add multiple items
nums.insert(1, 10)      # Insert at index
```

### Remove Elements

```python
nums.remove(10)         # Remove by value
nums.pop()              # Remove last item
nums.pop(1)             # Remove by index
del nums[0]             # Delete by index
nums.clear()            # Remove all items
```

### Search

```python
2 in nums
nums.index(2)
nums.count(2)
```

### Sort

```python
nums.sort()
nums.sort(reverse=True)
sorted(nums)
```

### Reverse

```python
nums.reverse()
```

### Copy

```python
copy = nums.copy()
```

### Useful Functions

```python
len(nums)
max(nums)
min(nums)
sum(nums)
```

---

## 2. Tuple `()`

### Create

```python
t = (1, 2, 3)
```

### Access

```python
t[0]
t[-1]
```

### Count & Index

```python
t.count(2)
t.index(3)
```

### Packing

```python
person = ("John", 25)
```

### Unpacking

```python
name, age = person
```

### Single Element Tuple

```python
single = (10,)
```

### Convert

```python
list(t)
tuple([1, 2, 3])
```

---

## 3. Set `{}`

### Create

```python
s = {1, 2, 3}
```

### Add

```python
s.add(4)
s.update([5, 6])
```

### Remove

```python
s.remove(2)      # Raises KeyError if missing
s.discard(2)     # No error if missing
s.pop()          # Removes an arbitrary element
s.clear()
```

### Membership

```python
3 in s
```

### Set Operations

```python
a = {1, 2, 3}
b = {3, 4, 5}

a | b    # Union
a & b    # Intersection
a - b    # Difference
a ^ b    # Symmetric Difference
```

### Subset / Superset

```python
a.issubset(b)
a.issuperset(b)
```

### Copy

```python
copy = s.copy()
```

---

## 4. Dictionary `{}`

### Create

```python
student = {
    "name": "John",
    "age": 25
}
```

### Read

```python
student["name"]
student.get("age")
```

### Add / Update

```python
student["city"] = "Pune"
student.update({"age": 26})
```

### Remove

```python
student.pop("age")
student.popitem()
del student["name"]
student.clear()
```

### Keys / Values

```python
student.keys()
student.values()
student.items()
```

### Check Key

```python
"name" in student
```

### Copy

```python
copy = student.copy()
```

### Iterate

```python
for key in student:
    print(key)

for key, value in student.items():
    print(key, value)
```

---

## 5. String (Bonus)

```python
text = "python"

text.upper()
text.lower()
text.title()
text.capitalize()

text.replace("py", "Py")
text.split("t")
"-".join(["a", "b", "c"])

text.startswith("py")
text.endswith("on")

text.find("th")
text.count("o")

len(text)
```

---

## 6. Useful Built-in Functions

```python
len(obj)
type(obj)
sorted(obj)
reversed(obj)

enumerate(lst)
zip(list1, list2)

any(lst)
all(lst)

sum(lst)
max(lst)
min(lst)
```

---

## 7. List Comprehension

```python
nums = [x * x for x in range(5)]

evens = [x for x in range(10) if x % 2 == 0]
```

---

## 8. Dictionary Comprehension

```python
square = {x: x * x for x in range(5)}
```

---

## 9. Set Comprehension

```python
unique = {x * x for x in range(5)}
```

---

## 10. Generator Expression

```python
gen = (x * x for x in range(5))
```

---

# Memory Trick

| Collection | Properties | Common Methods |
|------------|------------|----------------|
| **List `[]`** | Ordered, Mutable, Duplicates Allowed | `append()`, `extend()`, `insert()`, `remove()`, `pop()`, `sort()` |
| **Tuple `()`** | Ordered, Immutable | `count()`, `index()` |
| **Set `{}`** | Unordered, Unique Elements | `add()`, `remove()`, `discard()`, `union()`, `intersection()` |
| **Dictionary `{}`** | Key–Value Mapping | `get()`, `update()`, `keys()`, `values()`, `items()` |

---

# Most Asked Interview Methods

## List

- `append()`
- `extend()`
- `insert()`
- `remove()`
- `pop()`
- `sort()`
- `reverse()`
- `copy()`

## Tuple

- `count()`
- `index()`

## Set

- `add()`
- `update()`
- `remove()`
- `discard()`
- `union()`
- `intersection()`
- `difference()`

## Dictionary

- `get()`
- `update()`
- `keys()`
- `values()`
- `items()`
- `pop()`
- `popitem()`
