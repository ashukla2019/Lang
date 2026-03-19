/*
Set :
	Set is an associative container which we need to store unique elements.
	It always keeps the elements in sorted order.
        Set is implemented using binary search tree.
	Internally it maintains a balanced binary search tree of elements. Therefore, 
	when we search an element inside the set then it takes only log(n) complexity to search it.
*/

/*
Member functions
(constructor)		Construct set (public member function)
(destructor)		Set destructor (public member function)
operator=			Copy container content (public member function)

Iterators:
begin				Return iterator to beginning (public member function)
end					Return iterator to end (public member function)
rbegin				Return reverse iterator to reverse beginning (public member function)
rend				Return reverse iterator to reverse end (public member function)
cbegin				Return const_iterator to beginning (public member function)
cend				Return const_iterator to end (public member function)
crbegin				Return const_reverse_iterator to reverse beginning (public member function)
crend				Return const_reverse_iterator to reverse end (public member function)

Capacity:
empty				Test whether container is empty (public member function)
size				Return container size (public member function)
max_size			Return maximum size (public member function)

Modifiers:
insert				Insert element (public member function)
erase				Erase elements (public member function)
swap				Swap content (public member function)
clear				Clear content (public member function)
emplace				Construct and insert element (public member function)
emplace_hint		Construct and insert element with hint (public member function)

Observers:
key_comp			Return comparison object (public member function)
value_comp			Return comparison object (public member function)

Operations:
find				Get iterator to element (public member function)
count				Count elements with a specific value (public member function)
lower_bound			Return iterator to lower bound (public member function)
upper_bound			Return iterator to upper bound (public member function)
equal_range			Get range of equal elements (public member function)
*/

/*    |     set             | unordered_set
---------------------------------------------------------
Ordering        | increasing  order   | no ordering
                | (by default)        |

Implementation  | Self balancing BST  | Hash Table
                | like Red-Black Tree |  

search time     | log(n)              | O(1) -> Average 
                |                     | O(n) -> Worst Case

Insertion time  | log(n) + Rebalance  | Same as search
                      
Deletion time   | log(n) + Rebalance  | Same as search

/*
prefer set:
•	if you wish to filter multiple identical values
•	if you wish to parse items in a specified order (doing this in vector requires to specifically sort vector).
prefer vector:
•	if you want to keep identical values
•	if you wish to parse items in same order as you pushed them (assuming you don't process the vector order)
*/

// erasing from set
#include <iostream>
#include <set>

int main ()
{
	/****************Create/Initializations***********************/
		//initialize set with initializer list
		set<int>s = {10, 20, 30, 40,20};
		
		set<char> myset(str.begin(), str.end());

	/************Read/Access****************************/
		//To access a particular index, you can use this :
		 // using next() function
                auto it = next(s.begin(), n);
                // Printing the element at index n
                cout<<*it;

		  // Using advance function to
                  // access nth index
	           // Initializing iterator
                    auto it = s.begin();
                    advance(it,n);
		
	/**************Add/Insert***********************************/	
		// insert some values:
		for (int i=1; i<10; i++) myset.insert(i*10);  // 10 20 30 40 50 60 70 80 90

		it = myset.begin();
		++it;                                         // "it" points now to 20
		
	
	/************Remove data*****************************/
		myset.erase (it); //erase by position

		myset.erase (40); //erase value from set.

		it = myset.find (60);
		myset.erase (it, myset.end()); //erase values using range....

		myset.erase(myset.begin(), myset.end());
	  
		std::cout << "myset contains:";
		for (it=myset.begin(); it!=myset.end(); ++it)
			std::cout << ' ' << *it;
			std::cout << '\n';
	  

  return 0;
}
