/* Variable declaration in if and switch:
if(init; condition)
switch(init; condition)

Before C++17:
status s = check();
if(s!= success)
{
	return s;
}

Now with C++17:
if(status s = check(); s!= success)
{
	return s;
}

*/

##Before C++17:

int main()
{
    string str("Anki$t$");
    vector<char>vec(str.begin(), str.end());
    const auto it = find(vec.begin(), vec.end(), '$');
    if(it != vec.end())
    {
       *it = '#';
    }
    const auto it = find(vec.begin(), vec.end(), '$');
    if(it != vec.end())
    {
       *it = '#';
    }
    for(auto it: vec)
    {
        cout<<it<<endl;
    }

    return 0;
}

//Above code will throw error" error: conflicting declaration ‘const auto it"
//we can not use same it more than once in same scope. 
//solution is declaring variables inside if statements.

#Solution:

int main()
{
    string str("Anki$t$");
    vector<char>vec(str.begin(), str.end());
    if(const auto it = find(vec.begin(), vec.end(), '$'); //if(init; condition)
    it != vec.end())  
    {
       *it = '#';
    }
    if(const auto it = find(vec.begin(), vec.end(), '$');
    it != vec.end())
    {
       *it = '#';
    }
    
    for(auto it: vec)
    {
        cout<<it<<endl;
    }

    return 0;
}

//lockguard initialization and condition both together:
if(std::lock_guard<mutex>lg(m); !v.empty())
{
	
}


//structure binding and if with initializers:
map<string, int>mp{{"A", 10},{"B", 20}};
if(auto[key,val] = mp.insert("A", 10)); val!= 10)
{
	const auto& [key, val] = *pos;
}
