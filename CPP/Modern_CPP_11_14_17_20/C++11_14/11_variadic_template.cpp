Variadic template: are class or function templates, that can take any variable(zero or more)
number of arguments. In C++, templates can have a fixed number of parameters only that have to be specified
at the time of declaration. However, variadic templates help to overcome this issue.

/* Syntax
template(typename arg, typename... args)
return_type function_name(arg var1, args... var2)
*/
//Base case would called, when handling last argument: sum(var)
template<typename T>
T sum(T t)
{
    return t;
}

template<typename T1, typename... T2>
T1 sum(T1 var1, T2... var2)
{
    return var1 +sum(var2...);
}

int main()
{
    std::cout<<sum(1,2,3,4)<<std::endl;

    return 0;
}

Internal working:
/* First instantiated from: insights.cpp:17 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
int add<int>(int var1)
{
  return var1;
}
#endif

/* First instantiated from: insights.cpp:23 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
int add<int, int, int, int>(int var1, int __var21, int __var22, int __var23)
{
  return var1 + add(__var21, __var22, __var23);
}
#endif


/* First instantiated from: insights.cpp:17 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
int add<int, int, int>(int var1, int __var21, int __var22)
{
  return var1 + add(__var21, __var22);
}
#endif


/* First instantiated from: insights.cpp:17 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
int add<int, int>(int var1, int __var21)
{
  return var1 + add(__var21);
}
#endif
	

// Driver code
int main()
{
std::cout.operator<<(add(1, 2, 3, 4)).operator<<(std::endl);
return 0;
}
 
