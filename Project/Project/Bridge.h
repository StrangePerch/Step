#pragma once
#include "iostream.h"

class ILanguage
{
public:
	virtual void build() = 0;
	virtual void run() = 0;

};

class CPP : public ILanguage
{
public:
	void build()
	{
		cout << "CPP.build();" << endl;
	}
	void run()
	{
		cout << "CPP.run();" << endl;
	}
};

class Python : public ILanguage
{
public:
	void build()
	{
		cout << "Python.build();" << endl;
	}
	void run()
	{
		cout << "Phyton.run();" << endl;
	}
};

class Programer
{
protected:
	ILanguage* language;
public:
	Programer(ILanguage* language) : language(language) {}

	void setLanguage(ILanguage* language)
	{
		this->language = language;
	}
	virtual void getSalary() = 0;

	void work()
	{
		cout << "Programer.Work();" << endl;
		cout << "\t -> ";
		language->build();
		cout << "\t -> ";
		language->run();
	}
};

class Freelancer : public Programer
{
public:
	Freelancer(ILanguage* language) : Programer(language) {}
	void getSalary() override
	{
		cout << "Freelancer.getSalary();" << endl;
	}
};

class OfficeWorker : public Programer
{
public:
	OfficeWorker(ILanguage* language) : Programer(language) {}
	void getSalary() override
	{
		cout << "OfficeWorker.getSalary();" << endl;
	}
};