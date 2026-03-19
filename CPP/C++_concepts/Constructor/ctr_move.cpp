#include <iostream>
#include <cstring>

class myctr
{
	int id;
	char* name;
public:
	myctr() = default;
	
	myctr(int id, char* src) :id(id), name(new char[sizeof(src)+1]) {
		std::cout << "ctr\n";
		strcpy(name, src);
	}
	myctr(const myctr& src) :id(src.id), name(new char[sizeof(src.name)+1]) {
		strcpy(name, src.name);
		std::cout << "copy ctr\n";
	}

	myctr& operator=(const myctr & src) {
		id = src.id;
		name= new char[sizeof(src.name)+1];
		strcpy(name, src.name);
		std::cout << "Assignment optr\n";
		return *this;

	}

	myctr(myctr&& ctr) :id(ctr.id), name(ctr.name) {
		ctr.name = nullptr;
		std::cout << "move ctr\n";
	}

	myctr& operator=(myctr&& ctr) {
		id = ctr.id;
		name = ctr.name;
		std::cout << "move assignment optr\n";
		ctr.name = nullptr;
		return *this;

	}
	~myctr(){
		if (name)
			delete[] name;
	}
};

myctr fun() {
	return myctr(2, const_cast<char*>("A")); //RVO: return value optimization:compiler will perform copy elision/copy eliding so will not call move semantics
	//here, if we have to disable copy elision, Need to pass -fno-elide-constructors.
}

myctr test(myctr mctr)
{
	myctr temp(3, const_cast<char*>("B"));
	return temp; //NRVO: name return value optimization:compiler will perform copy elision/copy eliding so will not call move semantics
	//here, if we have to disable copy elision, Need to pass -fno-elide-constructors.
}



int main(){
	char* str = const_cast<char*>("ABC");
	myctr mctr1(1, str);
	myctr mctr2 = mctr1, mctr3;
	mctr3 = mctr2;
	//myctr mctr4 = std::move(mctr3);
	myctr mctr5 = fun(); //will call move ctr;
	//myctr mctr6 = test(myctr()); //will call move ctr;
	return 0;
}
