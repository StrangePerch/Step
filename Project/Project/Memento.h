#pragma once
#include "iostream.h"

class Memento
{
	int ammo;
	int hp;

	friend class Hero;
};

class Hero
{
	int ammo = 10;
	int hp = 100;
public:

	void save(Memento* mem)
	{
		mem->ammo = ammo;
		mem->hp = hp;
	}
	Memento* save()
	{
		Memento* mem = new Memento;
		mem->ammo = ammo;
		mem->hp = hp;
		return mem;
	}
	void load(Memento* mem)
	{
		ammo = mem->ammo;
		hp = mem->hp;
	}

	void shoot()
	{
		if (ammo)
		{
			ammo--;
			cout << "Shoot! Ammo left: " << ammo << endl;
		}
		else
		{
			cout << "NO AMMO" << endl;
		}
	}
};