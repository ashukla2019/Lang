1. LIST (Ordered, mutable, allows duplicates =>OMD)
	Create
	empty_list = []
	empty_list = list()
	lst = [1, 2, 3]
-----------	
	Read
	x = lst[0]      # index
	length = len(lst)
	sliced = lst[1:3]
-----------
	Update
	lst[0] = 100        # update value
	lst[1:3] = [20, 30] # update slice
 lst.append(4)
	lst.insert(1, 10)   # insert at index
	lst.extend([5, 6])
-------------
	Delete
	del lst[0]
	lst.remove(30)
	p = lst.pop()       # last element
	lst.clear()         # empty list
	
---------------------------------------------------------------
2. TUPLE (Ordered, immutable =>O)
	Create
	empty_tuple = ()
	empty_tuple = tuple()
	tup = (1, 2, 3)

	Read
	x = tup[0]
	sliced = tup[1:3]

	Update
	Tuples cannot be updated directly.
	But you can create a new tuple:

	tup = list(tup)
	tup[0] = 10
	tup = tuple(tup)

	Delete
	You cannot delete an item, only the entire tuple:
	del tup
----------------------------------------------------------------
3. SET (Unordered, mutable, no duplicates =>UM)
	Create
	empty_set = set()
	s = {1, 2, 3}
	------------
	Read
	No indexing! But you can loop or check membership:
	for i in s: print(i)
	exists = 3 in s
---------------
	Update
	Technically sets don’t support direct "update by index".
	But you can remove and add:
	s.remove(2)
	s.add(10)
 s.add(4)
	s.update([5, 6])

--------------
	Delete
	s.remove(3)       # error if not found
	s.discard(3)      # safe remove
	s.pop()           # removes arbitrary element
	s.clear()
-----------------------------------------------------------------
4. DICT (Dictionary) (Key-value pairs, mutable)
	Create
	empty_dict = {}
	empty_dict = dict()
	d = {"name": "Alice", "age": 25}
	d["city"] = "Seoul"     # add

	Read
	name = d["name"]
	age = d.get("age")
	keys = d.keys()
	values = d.values()
	items = d.items()

	Update
	d["age"] = 30
	d.update({"name": "Bob"})

	Delete
	del d["city"]
	removed = d.pop("age")
	d.clear()
--------------------------------------------------------------------------------------------------------------
Summary Table
Type	  Mutable	    Indexed	       CRUD Notes
List	  Yes	        Yes	           Full CRUD support
Tuple	  No	        Yes	           Only read; update = recreate
Set	      Yes	        No	           Unordered, no direct index update
Dict	  Yes	        Key-based	   CRUD using keys
