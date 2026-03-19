/*
template < class T, class Alloc = allocator<T> > class list;
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
	empty			Test whether container is empty (public member function)
	size			Return size (public member function)
	max_size		Return maximum size (public member function)
	
	Element access:
	front			Access first element (public member function)
	back			Access last element (public member function)

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


#include<iostream>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	/****************Create/Initializations***********************/
		//initialize list with default values
		//list<int>lt(5);
		
		//initialize list with same values
		//list<int>lt(5, 10);
		
		//initialize list with initializer list
		list<int>lt = {10, 20, 30, 40, 20};
		
		//initialize list with other container
		//string str("Hello");
		//list<char>lt(str.begin(), str.end());

	/************Read/Access****************************/
                front() - returns the first element of the list
                back() - returns the last element of the list
                // display the first element
                cout << "First Element: " << numbers.front() << endl;
  
                // display the last element
                cout << "Last Element: " << numbers.back();
		//C++ : How to get element by index in List: list doesn’t have operator []
		// Find 3rd element from list
		// It returns a new iterator pointing to n position after the
		// base iterator given as first argument
		auto it1 = std::next(listOfStrs.begin(), 2);
				
		/*iterate in reverse order:
		for(auto it = vec.rbegin(); it != vec.rend(); it++)
		{
			cout<<"values in list:"<<*it<<endl;
		}*/
		
	/**************Add/Update***********************************/
		//push_back and push_front
		//lt.push_front(11);
		//lt.push_back(18);
	        // using insert to insert
                // 2 element at the 4th position
                // inserts 2 occurrences
                // of 7 at 4th position
                list1.insert(it, 2, 7);
	
	
	/************Remove data*****************************/
                 1) pop_front() - removes the element at the beginning of the list
                 2) pop_back() - removes the element at the end of the list
                    // remove the first element of the list
                    numbers.pop_front();
                    // remove the last element of the list
                    numbers.pop_back();
		 3) Erase elements: can be removed by direct passing the value.
		    //erase element 30 
		    int y = 20;
		    lt.remove(y);
		    for(auto it = lt.begin(); it != lt.end(); it++)
		    {
			cout<<"values in list:"<<*it<<endl;
		    }
		//Erase elements by position and position range
		//lt.erase(lt.begin()); //by position but do not use like vec.begin()+1
		/*for(auto it = lt.begin(); it != lt.end(); it++)
		{
			cout<<"values in list:"<<*it<<endl;
		}*/
	
		//lt.erase(lt.begin(), lt.begin()); //by position range	
		//iterate list 
		/*for(auto it = lt.begin(); it != lt.end(); it++)
		{
			cout<<"values in list:"<<*it<<endl;
		}*/
	
		//Find element:
		/*
		int x = 20;
		auto it = find(lt.begin(), lt.end(), x);
		if(it != lt.end())
		{
			cout<<*it<<endl;
		}
		else
		{
			cout<<"No found"<<endl;
		}
		*/
	
	
	return 0;
}
