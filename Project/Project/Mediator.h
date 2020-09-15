#pragma once
#include "iostream.h"
#include "string.h"
#include "vector.h"


class Mediator
{
public:
	virtual void send(string message, Collegue* collegue) = 0;
};

class Collegue
{
protected:
	Mediator* mediator;
public:
	Collegue(Mediator* mediator) : mediator(mediator) {}
	void send(string message)
	{
		mediator->send(message, this);
	}
	virtual void notify(string message) = 0;
};

class SellerCollegue : public Collegue
{
public:
	SellerCollegue(Mediator* mediator) : Collegue(mediator) {}

	virtual void notify(string message)
	{
		cout << "Message to seller: " << message << endl;
	}
};

class ProgrammerCollegue : public Collegue
{
public:
	ProgrammerCollegue(Mediator* mediator) : Collegue(mediator) {}

	virtual void notify(string message)
	{
		cout << "Message to programmer: " << message << endl;
	}
};

class TesterCollegue : public Collegue
{
public:
	TesterCollegue(Mediator* mediator) : Collegue(mediator) {}

	virtual void notify(string message)
	{
		cout << "Message to tester: " << message << endl;
	}
};



class Manager : public Mediator
{
public:
	Collegue* seller;
	Collegue* programmer;
	Collegue* tester;
	void send(string message, Collegue* collegue)
	{
		if (collegue == seller) programmer->notify(message);
		else if (collegue == programmer) tester->notify(message);
		else seller->notify(message);
	}
};