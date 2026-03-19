/*
template < class T, class Alloc = allocator<T> > class vector; // generic template
std::allocator is the default memory allocator for the standard library containers, 
and you can substitute your own allocators. This allows you to control how the standard 
containers allocate memory
*/

/*
Operations:

	Member functions:
	(constructor)	Construct vector (public member function)
	(destructor)	Vector destructor (public member function)
	operator=		Assign content (public member function)
	
	Iterators:
	begin			Return iterator to beginning (public member function)
	end				Return iterator to end (public member function)
	rbegin			Return reverse iterator to reverse beginning (public member function)
	rend			Return reverse iterator to reverse end (public member function)
	cbegin			Return const_iterator to beginning (public member function)
	cend			Return const_iterator to end (public member function)
	crbegin			Return const_reverse_iterator to reverse beginning (public member function)
	crend			Return const_reverse_iterator to reverse end (public member function)
	
	Capacity:
	size			Return size (public member function)
	max_size		Return maximum size (public member function)
	resize			Change size (public member function)
	capacity		Return size of allocated storage capacity (public member function)
	empty			Test whether vector is empty (public member function)
	reserve			Request a change in capacity (public member function)
	shrink_to_fit	Shrink to fit (public member function)
	
	Element access:
	operator[]		Access element (public member function)
	at				Access element (public member function)
	front			Access first element (public member function)
	back			Access last element (public member function)
	data			Access data (public member function)

	
	Modifiers:
	assign			Assign vector content (public member function)
	push_back		Add element at the end (public member function)
	pop_back		Delete last element (public member function)
	insert			Insert elements (public member function)
	erase			Erase elements (public member function)
	swap			Swap content (public member function)
	clear			Clear content (public member function)
	emplace			Construct and insert element (public member function)
	emplace_back	Construct and insert element at the end (public member function)
/*

1.) Ordered Collection:
In std::vector all elements will remain in same order in which they are inserted.
2.) Provides random access:
Indexing is very fast in std::vector using opeartor [], just like arrays.
3.) Performance:
It Performs better if insertion and deletion is in end only and gives worst performance if insertion/deletion is at middle or at starting of vector.
4.) Contains Copy:
It always stores copy of the object not the same reference. So, if you are adding objects of user defined classes then you should define copy constructor and assignment operator in your class.
*/

/*
vector::push_back(): This modifier pushes the elements from the back.
vector::insert(): For inserting new items to a vector at a specified location.
vector::pop_back(): This modifier removes the vector elements from the back.
vector::erase(): It is used for removing a range of elements from the specified location.
vector::clear(): It removes all the vector elements.
*/

//How vector works internally:
/*
When std::vector’s internal memory completely finishes then it increases the size of its memory. To do that it performs following steps,

1.) It will allocate a bigger chunk of memory on heap i.e. almost double the size of previously allocated.
2.) Then it copies all the elements from old memory location to new one. Yes it copies them, so in case our elements are user defined objects then their copy constructor will be called. Which makes this step quite heavy in terms of speed.
3.) Then after successful copying it deletes the old memory.

*/

#include<iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	/****************Creation***********************/
		//initialize vector with default values
		//vector<int>vec(5);
		
		//initialize vector with same values
		//vector<int>vec(5, 10);
		
		//initialize vector with initializer list
		vector<int>vec = {10, 20, 30, 40,20};
		
		//initialize vector with other container
		//string str("Hello");
		//vector<char>vec(str.begin(), str.end());

	/************Read/Access****************************/
		//vector::at()
		vec.at(3);
	        Like an array, we can also use the square brackets [] to access vector elements. For example,
                vector<int> num {1, 2, 3};
                cout << num[1];  // Output: 2
		
	/**************Add/Insert***********************************/
	        push_back() invokes copy/move on the supplied object; emplace_back() constructs in place. 
		//insert value using push_back:
		//vec.push_back(50);
		
		//Insert element in vector:
		//vec.insert(vec.begin(), 7);

		#We can change an element of the vector using the same at() function.
	       // change elements at indexes 1 and 4
               num.at(1) = 9;
               num.at(4) = 7;	
	

	/************Remove data*****************************/
		//vec.pop_back();
		//iterate in reverse order:
		/*for(auto it = vec.rbegin(); it != vec.rend(); it++)
		{
			cout<<"values in vector:"<<*it<<endl;
		}*/
	
		//Find element:
		/*
		int x = 20;
		auto it = find(vec.begin(), vec.end(), x);
		if(it != vec.end())
		{
			cout<<*it<<endl;
		}
		else
		{
			cout<<"No found"<<endl;
		}
		*/
		//erase element 30 
		/*int y = 30;
		auto it = find(vec.begin(), vec.end(), y);
		if(it != vec.end())
		{
			vec.erase(it);
		}
		else
		{
			cout<<"No found"<<endl;
		}
		for(auto it = vec.begin(); it != vec.end(); it++)
		{
			cout<<"values in vector:"<<*it<<endl;
		}*/
		//Erase elements by position and position range
		//vec.erase(vec.begin()+1); by position
		//vec.erase(vec.begin(), vec.begin()+2); by position range	
		
		//Remove all occurrences of an element from vector in O(n) complexity:
		//int elem = 20;
		//vec.erase(std::remove(vec.begin(), vec.end(), elem), vec.end());
		/*for(auto it = vec.begin(); it != vec.end(); it++)
		{
			cout<<"values in vector:"<<*it<<endl;
		}*/
	return 0;
}



