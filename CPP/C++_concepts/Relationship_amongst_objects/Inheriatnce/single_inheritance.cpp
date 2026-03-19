#include<iostream>
using namespace std;

class Area
{
protected:
	int l,b; //private data members can not be accessed by Derived class
public:
	Area(int l, int b):l(l),b(b)
	{
		cout<<"Area ctor is called"<<endl;
	}	
	
};

class Volume: public Area
{
private:
	int h;
public:
	Volume(int l, int b, int h):Area(l, b),h(h){}
	void calculateVolume()
	{
		cout<<"volume is="<<(l*b*h)<<endl;;
	}
};

int main()
{
	Volume v(10,20,30);
	v.calculateVolume();
	return 0;
}
