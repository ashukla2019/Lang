/*
Creational Design Patterns: Creational patterns provide various object creation mechanisms, 
which increase flexibility and reuse of existing code.
Singleton: Define class that has only one instance and provides global point of access.
Requirement: one instance, global access, No ownership
Advantages: Save memory, Single access point(logger(error logging), database connection(single connection point to avoid corrupting data base), flexibility(change anytine)
Usage: Database application, Config settings(game settings, Application settings etc.)
*/

/*
Difference b/w static class and singleton:
Main differences are:
Singleton has an instance/object while static class is a bunch of static methods.
Singleton can be inherited which supports open/close principles in SOLID principles on the other hand static class can't be inherited and we need to make changes in itself.
Singleton object can be passed to methods while static class as it does not have instance can't be passed as parameters
*/

#include <iostream>
#include <string>

using namespace std;

class GameSetting
{
	static GameSetting* _instance;
	int _brightness;
	int _width;
	int _height;
	GameSetting() : _width(786), _height(1300), _brightness(75){}
	// all constructors should be private or public(iff you want to allow inheritance)

public:
	static GameSetting* getInstace() 
	{
		if(_instance == NULL) 
			_instance = new GameSetting();
		return _instance;
	}
	void setWidth(int width) 
	{
		_width = width;
	}
	void setHeight(int height) 
	{
		_height = height;
	}
	void setBrighness(int brightness) 
	{
		_brightness = brightness;
	}

	int getWidth() 
	{
		return _width;
	}
	int getHeight() 
	{
		return _height;
	}
	int getBrightness() 
	{
		return _brightness;
	}
	void displaySetting() 
	{
		cout << "brightness: " << _brightness << endl;
		cout << "height: " << _height << endl;
		cout << "width: " << _width << endl << endl;
	}
};

GameSetting * GameSetting::_instance = NULL;

void someFunction () 
{
	GameSetting *setting = GameSetting::getInstace();
	setting->displaySetting();
}

int main() 
{

	GameSetting *setting = GameSetting::getInstace();
	setting->displaySetting();
	setting->setBrighness(100);
	
	someFunction();
	return 0;
}
