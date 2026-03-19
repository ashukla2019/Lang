//Range-based for loop: C++11 bring in a new kind of for loop that iterates over all elements of a given range
//set of arrays or collection
for (declaration : coll/array_name )
{
// statement(s) block;
}
Ex: 1
for ( int i : { 2, 4, 6, 8, 10, 12, 14, 16 } )
{
std:: cout << "The Value :" << i << std:: endl;
}
Ex: 2
std:: vector<int> vect = {10,2,3,4};
for(auto & element :vect)
{
		std::cout<<"element"<<element<<std::endl;
}
