#include <iostream>
using namespace std;

#define MAX 5

template <typename T>
class MyVector {
	T arr[MAX];
	int top;
public:
	MyVector() :top(-1) {}
	void push_back(T val) { arr[++top] = val; }
	T operator [](int index) { return arr[index]; }
	class Iterator {
		MyVector *m_p;
		int index;
	public:
		Iterator(MyVector *p, int in) : m_p(p), index(in) {}
		bool operator !=(Iterator rhs) {
			if (this->m_p == rhs.m_p)
				if (this->index == rhs.index)
					return false;
			return true;
		}
		void operator ++() { index++; }
		T& operator * () { return m_p->arr[index]; }
	};
	Iterator begin() { return Iterator(this, 0); }
	Iterator end() { return Iterator(this, MAX); }
};

int main() {
	MyVector<int> vObj;

	for (int i = 0; i < MAX; i++)
		vObj.push_back(i);

	for (int i = 0; i < MAX; i++)
		cout << "MyVector<int>: vObj[" << i << "]= " << vObj[i] << "\n";

	cout << "------------------------\n";
	MyVector<int>::Iterator it = vObj.begin();

	for (; it != vObj.end(); ++it)
		cout << " *it= " << *it << "\n";
	
	cout << "------------------------\n";

	// range-based for-each loop: Requires begin and end member-functions in vObj-type.
	for ( auto it : vObj)
		cout << " [range_based]: *it= " << it << "\n";
	cout << "------------------------\n";

	return 0;
}
