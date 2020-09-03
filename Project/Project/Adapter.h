#pragma once

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;


class ITransport
{
public:
	virtual void drive() = 0;
};

class Car : public ITransport
{
public:
	void drive()
	{
		cout << "Car.drive();" << endl;
	}
};

class Camel
{
public:
	void walk()
	{
		cout << "Camel.move();" << endl;
	}
};

class Ship
{
public:
	void sail()
	{
		cout << "Ship.sail();" << endl;
	}
};

class ShipAdapter : public ITransport
{
	Ship* ship;
public:
	ShipAdapter(Ship* ship) : ship(ship)
	{
		cout << "ShipAdapter(Ship* ship);" << endl;
	}
	void drive()
	{
		cout << "ShipAdapter.drive();" << "  ->  ";
		ship->sail();
	}
};

class CamelAdapter : public ITransport
{
	Camel* camel;
public:
	CamelAdapter(Camel* camel) : camel(camel)
	{
		cout << "CamelAdapter(Camel* camel);" << endl;
	}
	void drive()
	{
		cout << "CamelAdapter.drive();" << "  ->  ";
		camel->walk();
	}
};


class Man
{
public:
	void travel(ITransport* car)
	{
		cout << "Man.travel();" << "  ->  ";
		car->drive();
	}
};
