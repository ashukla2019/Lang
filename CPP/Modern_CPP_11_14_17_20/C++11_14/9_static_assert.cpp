Static_Assert:
int main()
{
	int* ptr = NULL;
	assert(ptr != NULL); //Run-time assert
	static_assert(sizeof(int)==8, "Not 32-bit"); //compile-time assert(C++11)
}
