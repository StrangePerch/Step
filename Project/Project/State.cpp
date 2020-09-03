#include "State.h"

void Solid::heat()
{
	cout << "Ice melted to water" << endl;
	state = new Liquid;
}

void Solid::cold()
{
	cout << "Freezing ice" << endl;
}

void Gas::heat()
{
	cout << "Heating gas" << endl;
}

void Gas::cold()
{
	cout << "Gas turned into water" << endl;
	state = new Liquid;
}

void Liquid::heat()
{
	cout << "Water turned to gas" << endl;
	state = new Gas;
}

void Liquid::cold()
{
	cout << "Water freezed to ice" << endl;
	state = new Solid;
}
