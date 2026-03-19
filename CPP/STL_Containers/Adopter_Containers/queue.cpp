/*
template <class T, class Container = deque<T> > class queue;

Methods	Description
push()	inserts an element at the back of the queue
pop()	removes an element from the front of the queue
front()	returns the first element of the queue
back()	returns the last element of the queue
size()	returns the number of elements in the queue
empty()	returns true if the queue is empty

queue::size()	 O(1)
queue::emplace() O(1)
queue::front()	 O(1)
queue::back()	 O(1)
queue::push(g) 	 O(1)
queue::pop() 	 O(1)

*/

#include <iostream> 
#include <queue> 
using namespace std;

int main()
{
	//create a queue of string
	queue<string> animals;

	// push elements into the queue
	animals.push("Cat");
	animals.push("Dog");
  
	cout << "Queue: ";

	// print elements of queue
	// loop until queue is empty
	while(!animals.empty()) 
	{

		// print the element
		cout << animals.front() << ", ";

		// pop element from the queue
		animals.pop();
	}
	cout << endl;
 
  return 0;
}