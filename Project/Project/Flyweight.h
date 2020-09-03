#pragma once
#include "iostream.h"
#include "string.h"
#include <map>
using std::map;


class House
{
protected:
	int floor;
public:
	virtual void build(float x, float y) = 0;
};

class PanelHouse : public House
{
public:
	PanelHouse() { floor = 9; }

	void build(float x, float y) override
	{
		cout << "PanelHouse.build();" << endl;
		cout << "Floors - " << floor << endl;
		cout << "Cords ( " << x << ", " << y << " )" << endl;
	}
};

class BrickHouse : public House
{
public:
	BrickHouse() { floor = 4; }

	void build(float x, float y) override
	{
		cout << "BrickHouse.build();" << endl;
		cout << "Floors - " << floor << endl;
		cout << "Cords ( " << x << ", " << y << " )" << endl;
	}
};

class HouseFactory
{
	map<string, House*> houses;
public:
	HouseFactory()
	{
		houses["Panel"] = new PanelHouse;
		houses["Brick"] = new BrickHouse;
	}

	House* getHouse(string key)
	{
		if (houses.count(key))
			return houses[key];
		else
			return nullptr;
	}
};