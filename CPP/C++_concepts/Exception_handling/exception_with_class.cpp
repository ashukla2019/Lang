//When an exception is thrown, all objects created inside the enclosing 
//try block are destructed before the control is transferred to catch block.
class Test 
{
	public:
		Test() 
		{ 
			cout << "Constructor of Test " << endl; 
		}
		~Test() 
		{ 
			cout << "Destructor of Test " << endl; 
		}
};

int main() 
{
	try 
	{
		Test t1; //ctor will be called
		throw 10; //dtor will be called and then catch will be called.....
	} 
	catch(int i) 
	{
		cout << "Caught " << i << endl;
	}
}
