#include <iostream>
#include <vector>
using namespace std;

template <typename type>
struct MyAlloc: allocator<type>
{
	type* allocate(size_t size)
	{
		cout<<"allocation request size"<<size<<endl;
		return new type[size];
	}
	void deallocate(type* ptr, size_t size)
	{
		cout<<"deallocating size";
		delete[] ptr;
	}
	
};

int main()
{
	vector<int, MyAlloc<int>>vec; //Generally all containers provide allocator by default, if we 
	//want to use own allocator for memory allocation and deallocation.
	vec.push_back(10);
	for(auto it: vec)
	{
		cout<<it<<endl;
	}
	return 0;
}
