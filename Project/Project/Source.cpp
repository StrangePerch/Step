#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "Builder.h"


int main()
{
	MusicCenterBuilder a;
	ManualBuilder c; 
	Director b(c);
	b.buildMaxiMC();
	c.getResult()->print();
	b.setBuilder(a);
	b.buildMaxiMC();
	a.getResult()->print();

}