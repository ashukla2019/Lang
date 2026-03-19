#include <iostream>
using namespace std;

#if 0
struct Base {
	// void * vptr;
	// static void* vtable[];
	virtual void vfun() { cout << "Base::vfun\n"; } // virtual Base::vfun
	virtual void vfun2() { cout << "Base::vfun2222\n"; } // virtual Base::vfun2
};
/*
void * Base::vtable[0] = Base::vfun
void * Base::vtable[1] = Base::vfun2
*/

struct Derived :Base {
	// static void* vtable[];
	virtual void vfun() { cout << "Derived::vfun\n"; } // virtual Derived::vfun
	//virtual void vfun2() { cout << "Derived::vfun2222\n"; } // virtual Derived::vfun2
};
/*
void * Derived::vtable[0] = Base::vfun
void * Derived::vtable[1] = Derived::vfun2
*/

int main() {
	Base bObj;
	Derived dObj;
	
	Base *bp = &dObj; // LSP
	((void(*)()) (*((long*)(*((long*)bp))))) ();

	((void(*)())(*((1 + (long*)(*((long*)bp)))))) ();
	//bObj.vfun2();
	// call  ? //Base::vfun2

//	bp->vfun2();
	/*
	1. Derefer bp to reach vptr
	2. Derefer vptr to reach respective vtable
	3. Add offset of vfun2
	4. Derefer and fetch the member-function address
	5. Pass the args and make a call
	*/
	/*
	typedef void(*FNPTR) ();
	FNPTR fp1, fp2;

	long * p = (long*)bp;
	long *vptr = (long*)p;
	long *vtable = (long*)*vptr;

	fp1 = (FNPTR) *vtable;
	++vtable;
	fp2 = (FNPTR)*vtable;

	fp1();
	fp2();
	*/
}
#endif

#if 0
struct Derived; //forward declaration
struct Base {
	void fun();
	void vfun() { cout << "Base::vfun\n"; }
};

struct Derived : Base {
	void vfun() { cout << "Derived::vfun\n"; }
};

void Base::fun()
{
	cout << " Common logic 1111\n";
	cout << " Common logic 2222\n";
	//vfun();
	((Derived *)this)->vfun();
	cout << " Common logic 3333\n";
	cout << " Common logic 44444\n";
}
int main() {
	Derived dObj;

	dObj.fun(); // compile-time

	/*
	Base bObj;

	bObj.fun();
	*/
}
#endif

#if 0
template <typename T>
struct Base {
	void fun()
	{
		cout << " Common logic 1111\n";
		cout << " Common logic 2222\n";		
		(static_cast <T *>(this))->vfun();
		cout << " Common logic 3333\n";
		cout << " Common logic 44444\n";
	}
	void vfun() { cout << "Base::vfun\n"; }
};

struct Derived : Base< Derived>{ // CRTP => Curiously Recursive Template Pattern
	void vfun() { cout << "Derived::vfun\n"; }
};


int main() {
	Derived dObj;

	dObj.fun();
}
#endif


struct Base0 {}; // #1

struct Base : Base0 {
	// void *vptr
	// static void *vtable[]
	virtual void vf1() {}
	virtual void vf2() {}
};
// void *Base::vtable[0] = Base::vf1
// void *Base::vtable[1] = Base::vf2
struct D : Base {
	// static void *vtable[]
	void f2() {}
	void vf2() {} // virtual  void D::vf2
	void vf1() {} // virtual  void D::vf1
};
// void *D::vtable[0] =  D::vf1
// void *D::vtable[1] = D::vf2

void sizes() {
	cout << "sizeof(Base0)= " << sizeof(Base0) << "\n";
	cout << "sizeof(Base)= " << sizeof(Base) << "\n";
	cout << "sizeof(D)= " << sizeof(D) << "\n";
}
int main() {
	sizes();
}