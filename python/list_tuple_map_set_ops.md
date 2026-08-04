# Python CRUD Operations: List, Tuple, Dictionary (Map), and Set

## 1. List CRUD Operations

### Create
```python
lst = [10, 20, 30]
print(lst)
```

### Read
```python
print(lst[0])      # First element
print(lst[1])      # Second element
```

### Update
```python
lst[1] = 25        # Update element
lst.append(40)     # Add new element
print(lst)
```

### Delete
```python
lst.remove(25)     # Remove by value
lst.pop()          # Remove last element
del lst[0]         # Remove by index
print(lst)
```

---

## 2. Tuple CRUD Operations

> **Note:** Tuples are immutable, so update and delete operations on individual elements are not allowed.

### Create
```python
t = (10, 20, 30)
print(t)
```

### Read
```python
print(t[0])
print(t[1])
```

### Update
```python
# Not allowed
# t[1] = 25  ❌ TypeError
```

### Delete
```python
# Delete the entire tuple
del t
```

---

## 3. Dictionary (Map) CRUD Operations

### Create
```python
student = {
    "name": "Alice",
    "age": 20
}
print(student)
```

### Read
```python
print(student["name"])
print(student.get("age"))
```

### Update
```python
student["age"] = 21      # Update value
student["city"] = "Delhi" # Add new key-value pair
print(student)
```

### Delete
```python
del student["age"]
student.pop("city")
print(student)
```

---

## 4. Set CRUD Operations

### Create
```python
numbers = {10, 20, 30}
print(numbers)
```

### Read
```python
print(20 in numbers)   # True
print(40 in numbers)   # False
```

### Update
```python
numbers.add(40)
numbers.update([50, 60])
print(numbers)
```

### Delete
```python
numbers.remove(20)    # Removes 20
numbers.discard(30)   # Removes 30 (no error if absent)
numbers.pop()         # Removes an arbitrary element
print(numbers)
```

---

# CRUD Summary Table

| Data Structure | Create | Read | Update | Delete |
|---------------|--------|------|--------|--------|
| **List** | `lst = [10,20,30]` | `lst[0]` | `lst[1]=25`, `append()` | `remove()`, `pop()`, `del` |
| **Tuple** | `t = (10,20,30)` | `t[0]` | ❌ Not Allowed | ❌ Only `del t` |
| **Dictionary (Map)** | `d = {"a":1}` | `d["a"]`, `get()` | `d["a"]=2` | `del`, `pop()` |
| **Set** | `s = {10,20}` | `10 in s` | `add()`, `update()` | `remove()`, `discard()`, `pop()` |

---

# Key Differences

| Feature | List | Tuple | Dictionary | Set |
|---------|------|-------|------------|-----|
| Ordered | ✅ Yes | ✅ Yes | ✅ Yes | ❌ No |
| Mutable | ✅ Yes | ❌ No | ✅ Yes | ✅ Yes |
| Duplicate Values | ✅ Yes | ✅ Yes | ❌ Duplicate keys not allowed | ❌ No |
| Indexing | ✅ Yes | ✅ Yes | ❌ By key | ❌ No |
| Uses | Collection of items | Fixed collection | Key-value pairs | Unique elements |
