#pragma once
#include "iostream.h"

class Handler
{
protected:
	Handler* next;
public:
	Handler(){}
	Handler(Handler* next) : next(next) {}
	virtual void sendPayment(int sum) = 0;

	Handler* setNext(Handler* next)
	{
		this->next = next;
		return next;
	}
};

class Client
{
	Handler* next;
public:
	Client() {}
	Client(Handler* next) : next(next) {}
	void sendPayment(int sum)
	{
		if (sum > 1000)
		{
			if (next) next->sendPayment(sum);
		}
		else
		{
			cout << "Payment sended by client" << endl;
		}
	}
	Handler* setNext(Handler* next)
	{
		this->next = next;
		return next;
	}
};

class Economist : public Handler
{
public:
	Economist() {}
	Economist(Handler* next) : Handler(next) {}
	void sendPayment(int sum)
	{
		if (sum > 50000)
		{
			if (next) next->sendPayment(sum);
		}
		else
		{
			cout << "Payment sended by Economist" << endl;
		}
	}
};

class Buhgalter : public Handler
{
public:
	Buhgalter() {}
	Buhgalter(Handler* next) : Handler(next) {}
	void sendPayment(int sum)
	{
		if (sum > 250000)
		{
			if (next) next->sendPayment(sum);
		}
		else
		{
			cout << "Payment sended by Buhgalter" << endl;
		}
	}
};

class Director : public Handler
{
public:
	Director() {}
	Director() : Handler(nullptr) {}
	void sendPayment(int sum)
	{
		if (sum > 1000000)
		{
			if (next) next->sendPayment(sum);
			else cout << "This is too much even for Director" << endl;
		}
		else
		{
			cout << "Payment sended by Director" << endl;
		}
	}
};