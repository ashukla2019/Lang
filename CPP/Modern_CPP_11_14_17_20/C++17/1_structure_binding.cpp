/*
Initialize multiple identifiers/names from:
	-class/structure/union
	-pair/tuple/array
	-raw arrays
	
Types are derived from elements/members
*/

struct myStruct
{
	int i;
	double d;
};
myStruct ms;
auto [x,y] = ms; //Initialize multiple variables using structure.(auto obj = ms)
//then obj[0] = x and obj[1] = y
cout<<u<<v<<endl;

//It works with functions as well:
myStruct f1()
{
     myStruct ms= {5,2};
     return ms;
}
auto [x,y] = f1(); //Initialize multiple variables using return of function.
auto [w] = f1(); //Error: number of elements does not fit.

auto f2() ->int(&)[2]; //f2() returns a refeence to int array
auto [x,y] = f2() //x and y are initialized by elements of returned array

//with array
array<int,4>f3()
auto [i,j,k,l] = f3()

//with tuples:
tuple<int, float, string>f4()
auto [a,b,c] = f4()

//with map: Now no need to use first and second of iterator
map<string, double>mp;
for(const auto& [key,val]: mp)
{
	cout<<key<<":"<<val;
}
