#include <iostream>
#include "AbstractFactory.h"

using namespace std;

int main()
{
	Car* car = new Car;
	CarConfigurator conf;
	conf.setConfiguration(new MyCar);
	cout << "Before:" << endl;
	car->print();
	conf.configurate(car);
	cout << endl << "After:" << endl;
	car->print();

}