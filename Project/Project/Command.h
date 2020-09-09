#pragma once
#include "iostream.h"
#include "Windows.h"

class TV
{
public:
	void on()
	{
		cout << "TV.on();" << endl;
	}

	void off()
	{
		cout << "TV.off();" << endl;
	}
};

class ICommand
{
public:
	virtual void execute()
	{

	}
};

class TVCommandOn : public ICommand
{
	TV* tv;
public:
	TVCommandOn(TV* tv) : tv(tv){}
	void execute()
	{
		cout << "TVCommandOn.execute();" << endl;
		tv->on();
	}
};

class TVCommandOff : public ICommand
{
	TV* tv;
public:
	TVCommandOff(TV* tv) : tv(tv) {}
	void execute()
	{
		cout << "TVCommandOff.execute();" << endl;
		tv->off();
	}
};

class Controller
{
	ICommand* command;
public:
	Controller() {}
	Controller(ICommand* command) : command(command) {}
	
	void setCommand(ICommand* command)
	{
		cout << "Controller.setCommand();" << endl;
		this->command = command;
	}

	void button()
	{
		cout << "Controller.button();" << endl;
		command->execute();
	}
};

class Multivarka
{
public:
	void cook()
	{
		cout << "Cooking" << endl;
		int length = 10;
		for (size_t i = 0; i < length; i++)
		{
			cout << '-';
		}
		for (size_t i = 0; i < length; i++)
		{
			cout << "\b";
		}
		for (size_t i = 0; i < length; i++)
		{
			cout << '*';
			Sleep(500);
		}
		cout << endl << "Finish" << endl;
	}
};

class MVCommand : public ICommand
{
	Multivarka* mv;
public:
	MVCommand(Multivarka* mv) : mv(mv) {}
	void execute()
	{
		cout << "MVCommand.execute();" << endl;
		mv->cook();
	}
};