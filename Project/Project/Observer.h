#pragma once
#include "iostream.h"
#include "string.h"
#include "vector.h"

class Product;

class Buyer
{
public:
	virtual void update(Product* product) = 0;
};


class Product
{
protected:
	string name;
	struct Price
	{
		float old;
		float last;
	};

	Price price;

public:
	Product(string n, float p)
	{
		name = n;
		price.last = p;
		price.old = p;
	}

	string getName()
	{
		return name;
	}
	Price getPrice()
	{
		return price;
	}
	virtual void addBuyer(Buyer* buyer) = 0;
	virtual void delBuyer(Buyer* buyer) = 0;
	virtual void notify() = 0;

};

class Computer : public Product
{
	
	vector<Buyer*> buyers;
public:
	Computer(string n, float p) : Product(n,p) 
	{
		price.last = p;
	}

	void addBuyer(Buyer* buyer) override
	{
		buyers.push_back(buyer);
	}

	void delBuyer(Buyer* buyer)
	{
		auto del = find(buyers.begin(), buyers.end(), buyer);
		if (del != buyers.end())
			buyers.erase(del);
	}

	void notify() override
	{
		for (Buyer* a : buyers)
		{
			a->update(this);
		}
	}

	void setPrice(float p)
	{
		price.old = price.last;
		price.last = p;
		notify();
	}
};

class UkrainanBuyer : public Buyer
{
	string name;
public:
	UkrainanBuyer(string name) : name(name) {}
	void update(Product* product) override
	{
		cout << "Message for " << name << " about " << product->getName() << " product" << endl;
		cout << "Price changed from " << product->getPrice().old << " to " << product->getPrice().last << endl;
	}
};