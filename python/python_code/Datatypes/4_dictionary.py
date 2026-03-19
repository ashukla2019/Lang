#-----------------------------------------------------------------------------------------------------------------------------------------------

# Dictionary
# Dictionary in Python is an unordered collection of data values, used to store data values like a
# map. Dictionary holds key:value pair. Each key-value pair in a Dictionary is separated by a
# colon :, whereas each key is separated by a comma. A Dictionary can be created by placing a 
# sequence of elements within curly {} braces, separated by comma.
# Creating an empty Dictionary  
Dict = {}
print(Dict)  
 
# with Integer Keys  
Dict = {1: 'Geeks', 2: 'For', 3: 'Geeks'}
print(Dict)  
 
# with Mixed keys  
Dict = {'Name': 'Geeks', 1: [1, 2, 3, 4]}
print(Dict) 
'''
Output:

{}
{1: 'Geeks', 2: 'For', 3: 'Geeks'}
{1: [1, 2, 3, 4], 'Name': 'Geeks'}
'''

#Nested-Dictionary
# Creating a Nested Dictionary  
# as shown in the below image 
Dict = {1: 'Geeks', 2: 'For',  
        3:{'A' : 'Welcome', 'B' : 'To', 'C' : 'Geeks'}} 
   
print(Dict)  
'''
Output:

{1: 'Geeks', 2: 'For', 3: {'A': 'Welcome', 'B': 'To', 'C': 'Geeks'}}
'''

# Adding elements to a Dictionary: One value at a time can be added to a Dictionary by defining value along with the key e.g. Dict[Key] = Value.
# Creating an empty Dictionary 
Dict = {}
   
# Adding elements one at a time 
Dict[0] = 'Geeks'
Dict[2] = 'For'
Dict[3] = 1
print(Dict) 
 
   
# Updating existing Key's Value 
Dict[2] = 'Welcome'
print(Dict) 
'''
Output:

{0: 'Geeks', 2: 'For', 3: 1}
{0: 'Geeks', 2: 'Welcome', 3: 1}
'''

# Accessing elements from a Dictionary: In order to access the items of a dictionary refer to its key name or use get() method.
# Python program to demonstrate accessing an element from a Dictionary   
     
# Creating a Dictionary   
Dict = {1: 'Geeks', 'name': 'For', 3: 'Geeks'}  
     
# accessing a element using key
print(Dict['name'])  
   
# accessing a element using get()
print(Dict.get(3)) 
'''
Output:

For
Geeks
'''
# Removing Elements from Dictionary: Using pop() and popitem()
# Initial Dictionary  
Dict = { 5 : 'Welcome', 6 : 'To', 7 : 'Geeks',  
        'A' : {1 : 'Geeks', 2 : 'For', 3 : 'Geeks'},
       }  
     
# using pop()  
Dict.pop(5) 
print(Dict)  
 
# using popitem()  
Dict.popitem() 
print(Dict)  

'''
Output:

{'A': {1: 'Geeks', 2: 'For', 3: 'Geeks'}, 6: 'To', 7: 'Geeks'}
{6: 'To', 7: 'Geeks'}
'''
---------------------------------------------------------------------------------------------- 
class mydict():
    def __init__(self):
        #Empty dictionary
        self.mydict = dict()
        self.mydict = {}

    def create_dict(self):
        # Dictionary with Key-Value Pairs
        self.mydict = {"name": "Alice", "age": 25, "city": "New York"}

        # Using the dict() Constructor
        self.mydict = dict(name="Alice", age=25, city="New York")

        # From a List of Tuples
        self.mydict = dict([("name", "Alice"), ("age", 25)])

    def read_dict(self):
        # Using Keys
        print(self.mydict["name"])  # Alice

        # Using get() (to avoid KeyError if the key doesn't exist)
        print(self.mydict.get("age"))  # 25
        print(self.mydict.get("height", "Not found"))  # Not found

        # Checking Membership
        # Keys Only
        print("name" in self.mydict)  # True
        print("salary" not in self.mydict)  # True

        # Dictionary Methods
        # keys(): Returns a view of all keys.
        print(self.mydict.keys())  # dict_keys(['name', 'age', 'city'])

        #values(): Returns a view of all values.
        print(self.mydict.values())  # dict_values(['Alice', 25, 'New York'])

        #items(): Returns a view of all key - value pairs.
        print(self.mydict.items())  # dict_items([('name', 'Alice'), ('age', 25), ('city', 'New York')])

    def update_dict(self):
        # Adding and Updating Key - Value
        # Add a new key-value pair
        self.mydict["height"] = 170

        # Update an existing key
        self.mydict["age"] = 26

        # update(): Updates the dictionary with   key-value pairs from another dictionary or iterable.
        self.mydict.update({"age": 30, "city": "San Francisco"})

    def delete_dict(self):
        # pop(): Removes a key and returns its value.
        age = self.mydict.pop("age")  # Removes "age"

        # popitem(): Removes and returns the last inserted key-value pair (arbitrary before Python 3.7).
        last_item = self.mydict.popitem()

        # del: Deletes a key-value pair.
        del self.mydict["city"]

        # clear(): Removes all elements.
        self.mydict.clear()

    def __del__(self):
        if self.mydict:
            del self.mydict

if __name__ == '__main__':
    st = mydict()
    st.create_dict()
    st.read_dict()
    st.update_dict()
    st.read_dict()
    st.delete_dict()
