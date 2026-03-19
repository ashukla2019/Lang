#include <iostream>
using namespace std;

class student //this class's member function can access private,protected and public
{
private:
	int id;
protected:
	string blood_group;
public:
	string name;
	student():id(0),blood_group("O+"),name("Ankit"){}
	printStudData()
	{
		cout<<"id="<<id<<"\n";
	}
};

class teacher:public student //protected data and public data both can be accessed here
{
	public:
		teacher():student(){}
		void printdata()
		{
			cout<<"name="<<name<<"-------blood_group"<<blood_group<<"\n";
		}
};

int main()
{
	teacher t;
	t.printdata();
	t.printStudData();
	return 0;
}