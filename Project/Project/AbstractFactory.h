#pragma once

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

class Component
{
public:
	string name;
	virtual string getType() = 0;
};


/////////////
class Engine : public Component
{
public:
	int horse_power;
	int volume;
	Engine(int horse_power, int volume) : volume(volume), horse_power(horse_power) {}
};

class DieselEngine : public Engine
{
public:
	DieselEngine(int horse_power, int volume) : Engine(horse_power, volume) {}
	string getType() override
	{
		return "DieselEngine";
	}
};

class GasolineEngine : public Engine
{
public:
	GasolineEngine(int horse_power, int volume) : Engine(horse_power, volume) {}

	string getType() override
	{
		return "GasolineEngine";
	}
};

class GasEngine : public Engine
{
public:
	GasEngine(int horse_power, int volume) : Engine(horse_power, volume) {}


	string getType() override
	{
		return "GasEngine";
	}
};
/////////////

/////////////
class Hull : public Component
{

};

class Hatchback : public Hull
{
public:
	string getType() override
	{
		return "Hatchback";
	}
};

class Sedan : public Hull
{
public:
	string getType() override
	{
		return "Sedan";
	}
};

class Pickup : public Hull
{
public:
	string getType() override
	{
		return "Pickup";
	}
};
/////////////

/////////////
class GearBox : public Component
{

};

class Robot : public GearBox
{
public:
	string getType() override
	{
		return "Robot";
	}
};

class Variator : public GearBox
{
public:
	string getType() override
	{
		return "Variator";
	}
};

class Auto : public GearBox
{
public:
	string getType() override
	{
		return "Auto";
	}
};

class Manual : public GearBox
{
public:
	string getType() override
	{
		return "Manual";
	}
};
/////////////

class Car
{
	string name;
	Engine* engine = nullptr;
	Hull* hull = nullptr;
	GearBox* gearbox = nullptr;

public:

	Car(){}

	void setName(string name)
	{
		this->name = name;
	}

	void setEngine(Engine* engine)
	{
		this->engine = engine;
	}

	void setHull(Hull* hull)
	{
		this->hull = hull;
	}

	void setGearBox(GearBox* gearbox)
	{
		this->gearbox = gearbox;
	}

	Engine* takeoffEngine() 
	{ 
		Engine* temp = engine;
		engine = nullptr;
		return temp; 
	}
	Hull* takeoffHull()
	{
		Hull* temp = hull;
		hull = nullptr;
		return temp;
	}
	GearBox* takeoffGearBox()
	{
		GearBox* temp = gearbox;
		gearbox = nullptr;
		return temp;
	}


	string getName() { return name; }
	Engine* getEngine() { return engine; }
	Hull* getHull() { return hull; }
	GearBox* getGearBox() { return gearbox; }

	void print()
	{
		cout << "Name: " << name << endl;
		if (engine)
		{
			cout << "Engine: " << engine->name << endl;
			cout << "-Type: " << engine->getType() << endl;
			cout << "-Power: " << engine->horse_power << endl;
			cout << "-Volume: " << engine->volume << endl;
		}
		else
		{
			cout << "Engine: NULL" << endl;
		}
		if (hull)
		{
			cout << "Hull: " << hull->name << endl;
			cout << "-Type: " << hull->getType() << endl;
		}
		else
		{
			cout << "Hull: NULL" << endl;
		}

		if (gearbox)
		{
			cout << "GearBox: " << gearbox->name << endl;
			cout << "-Type: " << gearbox->getType() << endl;
		}
		else
		{
			cout << "GearBox: NULL" << endl;
		}
	}

	~Car()
	{
		delete engine;
		delete hull;
		delete gearbox;
	}

};

class ICarFactory
{
public:
	virtual string createName() = 0;
	virtual Engine* createEngine() = 0;
	virtual GearBox* createGearBox() = 0;
	virtual Hull* createHull() = 0;
};

class MyCar : public ICarFactory
{
public:
	string createName() { return "MyCar"; }
	Engine* createEngine() { return new DieselEngine(250, 2.5); }
	GearBox* createGearBox() { return new Variator; }
	Hull* createHull() { return new Pickup; }
};

class CarConfigurator
{
	ICarFactory* factory = nullptr;
public:
	~CarConfigurator() { delete factory; }
	void setConfiguration(ICarFactory* choice) { factory = choice; }
	void configurate(Car* car)
	{
		car->setName(factory->createName());
		car->setEngine(factory->createEngine());
		car->setHull(factory->createHull());
		car->setGearBox(factory->createGearBox());
	}
};