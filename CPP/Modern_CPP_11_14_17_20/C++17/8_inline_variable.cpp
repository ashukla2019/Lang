/*
static variables marked with inline count as definitions
-Guarnteed to exist only once in a program
-No need for CPP file to define static/global objects
*/

//monitor.hpp:
class monitor
{
	public:
		monitor() {}
};
//Declaring global monitor in header file, might be included by multiple 
//translation units.
inline monitor progmonitor;
