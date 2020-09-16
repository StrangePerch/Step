#pragma once
#include "iostream.h"


class Strategy
{
public:
	virtual float move(float len) = 0;
};

class WalkStrategy : public Strategy
{
	float speed = 5;
public:
	float move(float len) override
	{
		cout << "WalkStrategy.move(" << len << "); returned " << len / speed << " hours" << endl;
		return len / speed;
	}
};

class BusStrategy : public Strategy
{
public:
	float speed = 40;
	float move(float len) override
	{
		float traffic = (rand() % 100 + 100) / 100.f;
		cout << "BusStrategy.move(" << len << "); returned " << len / speed * 1.25 * traffic << " hours" << endl;
		return len / speed * 1.25 * traffic;
	}
};

class CarStrategy : public Strategy
{
public:
	float speed = 50;
	float move(float len) override
	{
		float traffic = (rand() % 100 + 100) / 100.f;
		cout << "CarStrategy.move(" << len << "); returned " << len / speed * traffic << " hours" << endl;
		return len / speed * traffic;
	}
};

class Navigator
{
	Strategy* strategy;
public:
	void setStrategy(Strategy* strategy)
	{
		this->strategy = strategy;
	}
	float getTime(float len)
	{
		return strategy->move(len);
	}
};