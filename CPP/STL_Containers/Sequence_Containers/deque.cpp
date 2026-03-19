#include<iostream>
#include <deque>
#include <algorithm>
using namespace std;

int main()
{
	/****************Create/Initializations***********************/
		//initialize deque with default values
		//deque<int>dq(5);
		
		//initialize deque with same values
		//deque<int>dq(5, 10);
		
		//initialize deque with initializer list
		deque<int>dq = {10, 20, 30, 40, 20};

		//Using other containers:
		std::vector<int> vec = {10, 20, 30};
                std::deque<int> dq(vec.begin(), vec.end());

	/************Read/Access****************************/
      		front() - returns the first element at front
       		back() - returns the last element at back
       		at() - returns element at the specified inde
		dq[1] - Random access
				
	/**************Add***********************************/
		//push_back and push_front
		//dq.push_front(11);
		//dq.push_back(18);
	      
	/************Remove data*****************************/
                 1) pop_front() - removes the element at the front
                 2) pop_back() - removes the element at the back
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

