#pragma once
#include "string.h"
#include "iostream.h"
#include "map.h"

class IPage
{
public:
	virtual string getPage(int key) = 0;
};

class DataBase : public IPage
{
	map<int, string> pages;
public:
	DataBase()
	{
		pages[1] = "Page1";
		pages[2] = "Page2";
		pages[3] = "Page3";
		pages[4] = "Page4";
		pages[5] = "Page5";
	}

	string getPage(int key) override
	{
		if (pages.count(key))
			return pages[key];
		else
			return "no page";
	}

};

class DataBaseProxy : public IPage
{
	map<int, string> cash;
	DataBase* base;
public:
	string getPage(int key) override
	{
		if (cash.count(key)) return cash[key];
		else
		{
			base = new DataBase;
			string page = base->getPage(key);
			cash[key] = page;
			delete base;
			return page;
		}
	}
};