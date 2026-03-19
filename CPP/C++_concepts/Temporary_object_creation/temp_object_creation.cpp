#include <iostream> 
#include <vector>
#include <vector> 
using namespace std;

class A 
{ 
    int *ptr;
public:
	//Conversion constructor
	A()=default;
    A(int x)
    { 
        //cout <<"Calling conversion constructor"<<endl; 
        ptr = new int; 
        *ptr = x;
    }
	//Copy Constructor:copy of object is created
    A( const A & obj)
    { 
        this->ptr = new int;
        *ptr = *(obj.ptr); // Deep copying
        cout <<"Calling Copy constructor"<<endl;
    }
	// Move ctor: It will simply shift the resources of rvalue to lvalue without creating a copy.
    A ( A && obj)
    {
        cout <<"Calling Move constructor"<<endl; 
        this->ptr = obj.ptr;
        obj.ptr = NULL;
    }
	//Assignment operator
    A& operator=( const A & obj)
    { 
        this->ptr = new int;
        *ptr = *(obj.ptr); 
        cout <<"Assignment operator"<<endl;
		return *this;
    }
	//Move Assignment operator
    A& operator= ( A && obj)
    {
        cout <<"Calling Move assignment operator"<<endl; 
        this->ptr = obj.ptr;
        obj.ptr = NULL;
		return *this;
    }
	A operator+(A& obj)
	{
		A temp; 
		*temp.ptr = *obj.ptr + *this->ptr;
		return temp; //this will also call move ctor, returning object by value.
	}
    // Destructor
    ~A()
    { 
       
        //cout<<"Calling Destructor"<<endl;
        delete ptr;
    }
        
    void display()
    {
        cout<<"value is:"<<*ptr<<endl;
            
    }
};

A fun()
{
	A a2;
    return a2;

}

void fun(int& i) //this can be called, as it's for lvalue reference.
{
	
}

int fun(const int& i) //this can be called, as it's for lvalue reference.
{
	
}


int main()
{
    A a1(10); //calling conversion constructor//
	A a2(20);
    //A a3 = fun(); //will call move constructor: A _temp = fun(): function returning by value
	//A a3 = a1 + a2; //A _temp = a1+a2 //temporary object will be created. expression evaluation.
    //vector <A> vec;
    //vec.push_back(A(10));
	fun(10); //argument passing: 
    return 0;
    
}






/*
class Foo
{
    private:
    int* array, size;

    public:
    Foo(int s)
    {
        size = s;
        array = new int[size] {0};
    }


    // copy constructor
    // Foo g(f); where g is a Foo
    // Foo g = f;
    Foo(const Foo& rhs)
    {
        cout << "Copy constructor executes." << endl;
        size = rhs.size;   
        array = new int[size];

        for(int i = 0; i < size; i++)
            array[i] = rhs.array[i];
    }

    // move constructor: for dealing r-values...
    Foo(Foo&& rhs) noexcept
    {
        cout << "move constructor executes." << endl;
        size = rhs.size;
        array = rhs.array;
        rhs.array = nullptr;
    }

    ~Foo()
    {
        if(array)
            delete [] array;
    }

    // f + g; cause an r-value to be created
    Foo operator+(const Foo& rhs)
    {
        Foo temp(size + rhs.size);

        auto i = 0;
        for(; i < size; i++)
            temp[i] = array[i];

        for(auto j = 0; j < rhs.size; i++, j++)
            temp[i] = rhs.array[j];

        return temp;
    }
    
    // f = g;
    Foo& operator=(const Foo& rhs)
    {
        cout << "Copy assignment operator executes." << endl;
        if(this == &rhs)
            return *this;

        if(array)
            delete [] array;

        size = rhs.size;
        array = new int[size];

        for(int i = 0; i < size; i++)
            array[i] = rhs.array[i];

        return *this;
    }

    // move assignment operator
    Foo& operator=(Foo&& rhs) noexcept
    {
        cout << "move assignment operator executes." << endl;
        size = rhs.size;
        array = rhs.array;
        rhs.array = nullptr;

        return *this;
    }


    int& operator[](int i)
    { return array[i]; }

    int length() const
    { return size; }

    friend ostream& operator<<(ostream& o, const Foo& rhs)
    {
        for(int i = 0; i < rhs.size; i++)
            o << rhs.array[i] << " ";

        return o;
    }
};

int main()
{
    Foo f(5);

    for(int i = 0; i < f.length(); i++)
        f[i] = 3 * i;

    cout << f << endl;

    Foo g(f);
    cout << g << endl;

    //Foo h(3);

    //cout << h << endl;

	cout<<"****************\n";
    // f + g creates an r-value...that's an unnamed memory location that is TEMPORARY.
    // that temp r-value...(expression evaluation)
    Foo h = f + g;

    //cout << h << endl;
    //cin.get();
}
*/