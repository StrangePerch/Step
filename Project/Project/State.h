#pragma once
#include "iostream.h"

class IWaterState
{
protected:
	IWaterState* state;
public:

	virtual void heat() = 0;
	virtual void cold() = 0;
	IWaterState* newState() { return state; }
};

class Gas : public IWaterState
{
public:
	Gas()
	{
		state = this;
	}
	void heat();
	void cold();
};

class Solid : public IWaterState
{
public:
	Solid()
	{
		state = this;
	}
	void heat();
	void cold();
};

class Liquid : public IWaterState
{
public:
	Liquid()
	{
		state = this;
	}
	void heat();
	void cold();
};

class Water
{
	IWaterState* state = new Liquid;

	void reloadState()
	{
		IWaterState* temp = state->newState();
		if (temp == state) return;
		delete state;
		state = temp;
	}	
public:
	void heat()
	{
		state->heat();
		reloadState();
	}
	void cold()
	{
		state->cold();
		reloadState();
	}
};
