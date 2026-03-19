//Nullptr:To avoid mistakes which might occur when a null pointer gets interpreted as an integral value. 
Type-Safety
nullptr is of type std::nullptr_t
It can only convert to pointer types, not integers

void fun(char* s)
{
	cout<<"inside fun(char*)"<<endl;
}
void fun(int x)
{
	cout<<"inside fun(int)"<<endl;
}
int main()
{
	fun(NULL); //There will be an error to find matching function, since NULL is macro. 
	           //C++ introduced nullptr to avoid confusion.
}
