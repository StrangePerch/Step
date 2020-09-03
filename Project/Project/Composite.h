#pragma once
#include "string.h"
#include "iostream.h"
#include "list.h"

class Component
{
protected:
	string name;
public:
	Component(string name) : name(name) {}
	virtual void add(Component* comp) {}
	virtual void print(int step = 1)
	{
		cout << "-" << name << ".file" << endl;
	}

};

class Folder : public Component
{
	list<Component*> components;
public:
	Folder(string name) : Component(name) {}
	void add(Component* comp) override
	{
		components.push_back(comp);
	}
	void print(int step = 1) override
	{
		cout << ">" << name << endl;
		for (Component* comp : components)
		{
			for (size_t i = 0; i < step; i++)
			{
				cout << " ";
			}
			comp->print(step + 1);
		}
	}
};

class File : public Component
{
public:	
	void add(Component* comp) override {};
	File(string name) : Component(name) {}
};
