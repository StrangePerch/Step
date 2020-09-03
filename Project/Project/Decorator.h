#pragma once

#include <iostream>

using namespace std;

class Pizza
{
	string name;
public:

	Pizza(string name) : name(name) {}

	string getName() { return name; }

	virtual int getCost() = 0;

	virtual Pizza* get_next()
	{
		return nullptr;
	}
};

class ItalianPizza : public Pizza
{
public:
	ItalianPizza() : Pizza("ItalianPizza") {}
	int getCost() override
	{
		return 100;
	}
};

class UkrainianPizza : public Pizza
{
public:
	UkrainianPizza() : Pizza("UkrainianPizza") {}
	int getCost() override
	{
		return 150;
	}
};

class PizzaDecorator : public Pizza
{
protected:
	Pizza* pizza;
public:
	PizzaDecorator(Pizza* pizza, string name) : pizza(pizza), Pizza(name) {}
	//virtual ~PizzaDecorator() { delete pizza; }
	Pizza* get_next() override
	{
		return pizza;
	}
};

class Meat : public PizzaDecorator
{
public:
	Meat(Pizza* pizza) : PizzaDecorator(pizza, pizza->getName() + " + meat"){}
	int getCost()
	{
		return pizza->getCost() + 30;
	}
};

class Tomato : public PizzaDecorator
{
public:
	Tomato(Pizza* pizza) : PizzaDecorator(pizza, pizza->getName() + " + tomato") {}
	int getCost()
	{
		return pizza->getCost() + 10;
	}
};

class Cheese : public PizzaDecorator
{
public:
	Cheese(Pizza* pizza) : PizzaDecorator(pizza, pizza->getName() + " + cheese") {}
	int getCost()
	{
		return pizza->getCost() + 20;
	}
};

/*
void pop_back(Pizza*& pizza)
{
	Pizza* temp;
	temp = pizza->get_next();
	delete pizza;
	pizza = temp;
}

int main()
{
	Pizza* pizza = new UkrainianPizza;
	pizza = new Meat(pizza);
	pizza = new Tomato(pizza);
	pizza = new Meat(pizza);
	pizza = new Cheese(pizza);
	cout << "Name: " << pizza->getName() << ", cost: " << pizza->getCost() << endl;
	pop_back(pizza);
	cout << "Name: " << pizza->getName() << ", cost: " << pizza->getCost() << endl;

}
*/