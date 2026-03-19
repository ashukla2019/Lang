Strongly typed Enums:

problems with existing enums:
enum apple{green =0, red =1};
enum orange{big =0, small =1};
int main()
{
	apple a = green;
	orange o = big;
	if(a ==o) //this becomes true while both enum type is not of same type. it is compared
	 //at compile time.
	{
		cout<<"true"<<endl;
	}
}
//solution is: Strongly typed Enums:
enum class apple{green =0, red =1};
enum class orange{big =0, small =1};
int main()
{
	apple a = apple::green;
	orange o = orange::big;
	if(typeid(a) == typeid(o))
	{
		cout<<"true"<<endl;
	}
}

