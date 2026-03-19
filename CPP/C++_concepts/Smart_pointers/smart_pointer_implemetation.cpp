#include<iostream>
using namespace std;

class Person
{
    int age;
    char* pName;

    public:
        Person(): pName(0),age(0)
        {
        }
        Person(char* pName, int age): pName(pName), age(age)
        {
        }
        ~Person()
        {
			cout<<"destructor is called";
        }
        void Display()
        {
            cout<<"Name ="<<pName<<"\n"<<"Age ="<<age<<"\n";
        }
       
};

template<typename T>
class SP
{
private:
    T*    pData; // pointer to person class
public:
    SP(T* pValue) : pData(pValue)
    {
    }
    ~SP()
    {
        // pointer no longer requried
        delete pData;
    }

    T& operator* ()
    {
        return *pData;
    }

    T* operator-> ()
    {    
        return pData;
    }
};


int main()
{
    SP<Person>p(new Person(const_cast<char*>("Scott"), 25));
    //SP p(new Person(const_cast<char*>("Scott"), 25));
    p->Display();
    //delete pPerson;
}
-------------------------------------------------------------------------------------------------------------------  
#include <iostream>
#include<tuple>
#include <memory>

using namespace std;

class user
{
	int user_id;
	string user_name;
public:
	user()=default;
	user(int id, string name):user_id(id), user_name(name){
	}
	pair<int, string>getUserDetails(){
		return make_pair(user_id, user_name);
	}
};

template<typename T>
class smart_ptr{
	T* usr;
public:
	smart_ptr()=default;
	smart_ptr(T* t):usr(t){
	}
	T* operator->(){
		return usr;
	}
	~smart_ptr(){
		if (usr)
			delete usr;
	}
};

int main(){
	string s("Ankit");
	//user u(1, s);
	smart_ptr<user>u(new user(1, s));
	auto [id, name] = u->getUserDetails(); 
	cout<<"user-id="<<id<<" "<<"user_name="<<name<<"\n";
	return 0;
}
