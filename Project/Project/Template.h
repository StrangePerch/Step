#pragma once
#include "iostream.h"

class TemplateBuild
{
protected:
	virtual void name() = 0;
	virtual void buildFoundation() = 0;
	virtual void buildWall() = 0;
	virtual void buildDoor() = 0;
	virtual void buildWindows(int count) = 0;
	virtual void buildRoof() = 0;
	virtual void first_hook() = 0;
	virtual void second_hook() = 0;
public:

	void start(const int count)
	{
		name();
		buildFoundation();
		buildWall();
		buildWindows(count);
		buildDoor();
		first_hook();
		buildRoof();
		second_hook();
	}
};

class MegaHouse final : public TemplateBuild
{
	void name() override
	{
		cout << "MegaHouse:" << endl;
	}

	void buildFoundation() override
	{
		cout << "Expensive reinforced concrete foundation" << endl;
	}

	void buildWall() override
	{
		cout << "Wooden Walls from iron tree" << endl;
	}

	void buildWindows(const int count) override
	{
		cout << "Mega thermal, sound isolating " << count << " windows from ultra plastic" << endl;
	}

	void buildDoor() override
	{
		cout << "HandMade reinforced doors from oak" << endl;
	}

	void first_hook() override
	{
		cout << "Fireplace" << endl;
	}

	void buildRoof() override
	{
		cout << "Panorama roof" << endl;
	}

	void second_hook() override
	{
		cout << "And finally pool" << endl;
	}
};

class NormalHouse final : public TemplateBuild
{
	void name() override
	{
		cout << "NormalHouse:" << endl;
	}

	void buildFoundation() override
	{
		cout << "Concrete foundation" << endl;
	}

	void buildWall() override
	{
		cout << "Clue walls" << endl;
	}

	void buildWindows(const int count) override
	{
		cout << "Wooden windows in count " << count << endl;
	}

	void buildDoor() override
	{
		cout << "Normal wooden door" << endl;
	}

	void first_hook() override
	{
	}

	void buildRoof() override
	{
		cout << "Straw roof" << endl;
	}

	void second_hook() override
	{
	}
};