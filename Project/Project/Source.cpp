#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "Adapter.h"

int main()
{
	Car* car = new Car;
	Man* man = new Man;
	Camel* camel = new Camel;
	Ship* ship = new Ship;
	man->travel(car);
	man->travel(new CamelAdapter(camel));
	man->travel(new ShipAdapter(ship));
}