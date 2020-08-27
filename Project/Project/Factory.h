#pragma once

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;


//## Product
class Transport
{
public:
	virtual void delivery(string adress) = 0;
};
//##

//## Concrete product
class Plane : public Transport
{
	void delivery(string adress) override
	{
		cout << "Plain delivered package to " << adress << endl;
	}
};

class Car : public Transport
{
	void delivery(string adress) override
	{
		cout << "Car delivered package to " << adress << endl;
	}
};

class Ship : public Transport
{
	void delivery(string adress) override
	{
		cout << "Ship delivered package to " << adress << endl;
	}
};

class Train : public Transport
{
	void delivery(string adress) override
	{
		cout << "Train delivered package to " << adress << endl;
	}
};
//##



class Factory
{
public:

	virtual Transport* createTransport() = 0;

	Transport* create()
	{
		Transport* transport = this->createTransport();
		return transport;
	}
};

class CarFactory : public Factory
{
public:
	Transport* createTransport() override
	{
		return new Car;
	}
};

class ShipFactory : public Factory
{
public:
	Transport* createTransport() override
	{
		return new Ship;
	}
};

class TrainFactory : public Factory
{
public:
	Transport* createTransport() override
	{
		return new Train;
	}
};

class PlaneFactory : public Factory
{
public:
	Transport* createTransport() override
	{
		return new Plane;
	}
};