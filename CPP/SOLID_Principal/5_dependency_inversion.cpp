Dependency inversion principal:
low coupling. High level module should not depend on low level module. 
Both should depend on abstract interfaces/classes not on the concrete classes.

Problematic code:
class mycloud
{
public:
	void upload(string filepath);
};

class fileUploader
{
public:
		fileUploader(mycloud& mcl); //it depends on myCloud which is wrong...should depend on abstraction.
};

//Correction:
class cloud
{
public:
	void upload(string filepath)=0;
};

class mycloud:public cloud
{
public:
	void upload()
	{
		cout<<""<<endl;
	}
};
class fileUploader
{
public:
		fileUploader(cloud& cl); 
};
