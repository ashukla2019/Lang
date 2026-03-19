/*
template <class T, class Container = deque<T> > class stack;

empty() – Returns whether the stack is empty – Time Complexity : O(1) 
size() – Returns the size of the stack – Time Complexity : O(1) 
top() – Returns a reference to the top most element of the stack – Time Complexity : O(1) 
push(g) – Adds the element ‘g’ at the top of the stack – Time Complexity : O(1) 
pop() – Deletes the top most element of the stack – Time Complexity : O(1) 

*/


#include <iostream> 
#include <stack> 
using namespace std;
int main() 
{
	/***********Initialization********************/
		//stack can be initialized using other containers like: vector, dequeue...
		std::deque<int> mydeque (3,100)
		stack<int> st(mydeque);
		
	/**************Add/Insert***********************************/
		st.push(10);
		st.push(20);
		st.push(30);
		st.push(40);
		
	/************Access****************************/
		st.top();
		
	/************Remove data*****************************/
		st.pop();
		st.pop();

	while (!st.empty()) 
	{
		cout << ' ' << st.top();
		st.pop();
	}
}