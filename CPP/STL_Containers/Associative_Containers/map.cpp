/*
Map:  is used to store key-value pairs. Multimap is nothing different than a normal map except the fact that in a multimap mutiple values can have the same key.
	Map is an associative container that is used to store key-value pair of elements with unique keys.
	It always keeps the inserted pairs in sorted order based on the key.
	Internally it maintains a balanced binary search tree to store keys. Therefore, 
	when searching key inside the map takes only log(n) complexity.
	We cannot modify the key of any inserted pair in map.
	We can modify the value associated with a key in any inserted pair in map.  
*/

/*
Member functions
(constructor)		Construct map (public member function)
(destructor)		Map destructor (public member function)
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

Element access:
operator[]			Access element (public member function)
at					Access element (public member function)

Modifiers:
insert				Insert elements (public member function)
erase				Erase elements (public member function)
swap				Swap content (public member function)
clear				Clear content (public member function)
emplace				Construct and insert element (public member function)
emplace_hint		Construct and insert element with hint (public member function)

Observers:
key_comp			Return key comparison object (public member function)
value_comp			Return value comparison object (public member function)

Operations:
find				Get iterator to element (public member function)
count				Count elements with a specific key (public member function)
lower_bound			Return iterator to lower bound (public member function)
upper_bound			Return iterator to upper bound (public member function)
equal_range			Get range of equal elements (public member function)
*/

#include <iostream>
#include <map>

using namespace std;

int main()
{
	/****************Create/Initializations***********************/
		/*
		map<char,int> first;
	  
		//initializing
		first['a']=10;
		first['b']=20;
		first['c']=30;
		first['d']=40;
		*/
		map<char,int> first = {{'a', 10}, {'b', 20}};
		for(auto it=first.begin(); it!=first.end(); ++it)
		{
			cout << it->first << " => " << it->second << '\n';
		}

	/************Access****************************/
		//can access element using .at or []
		//cout<<first.at('a')<<endl;
	/**************Add/Insert***********************************/
		//Inserting data with insert member function.

		first.insert(make_pair('e', 50));
		first.insert(make_pair('f', 60));
		
		first.insert(make_pair('g', 70));
		first.insert(make_pair('h', 80));
		
		for(auto it=first.begin(); it!=first.end(); ++it)
		{
			cout << it->first << " => " << it->second << '\n';
		}
		
	
	/************Remove data*****************************/
		// function to erase given keys
		first.erase('e');
		first.erase('f');

		// map::erase(iterator position)
		// function to erase given position
		auto it = first.find('a');
		first.erase(it);
			
		// erasing a given range:
		// the position where the element is
		auto it1 = first.find('g');
		auto it2 = first.find('h');
		first.erase(it1, it2);
	return 0;
	
}
	
