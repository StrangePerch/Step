#include "iostream.h"
#include "string.h"
#include "fstream.h"
#include <time.h>

#include "Memento.h"

int main()
{
	Hero* hero = new Hero;
	Memento* mem = hero->save();
	for (size_t i = 0; i < 7; i++)
	{
		hero->shoot();
	}
	hero->load(mem);
	for (size_t i = 0; i < 15; i++)
	{
		hero->shoot();
	}
}