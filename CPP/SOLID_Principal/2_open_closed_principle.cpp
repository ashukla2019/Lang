//Problematic code:
class pizzaProviders
{
public:
	void buildPizza(int choice)
	{
		switch (choice)
		{
		case 1: 
			void builtByDominos();
			break;
		case 2:
			void builtByMojo();
			break;
		}
	}
};
implementation using openclosed principle:
class pizzaMakers
{
public:
	void virtual preparePizza()= 0;
};

class Dominos : public pizzaMakers
{
	void preparePizza() {}
};

class Mojo : public pizzaMakers
{
	void preparePizza() {}
};

int main()
{
	pizzaMakers* pmaker(new Dominos());
	pmaker->preparePizza();
	return 0;
}
