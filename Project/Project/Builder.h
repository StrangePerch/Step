#pragma once
#include <vector>
#include <string>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cin;

class BaseComponent
{
public:
	virtual string getName()
	{
		return "Base";
	}
};

class Radio : public BaseComponent
{
public:
	string getName() override
	{
		return "Radio";
	}
};

class BlueRay : public BaseComponent
{
public:
	string getName() override
	{
		return "BlueRay";
	}
};

class DVD : public BaseComponent
{
public:
	string getName() override
	{
		return "DVD";
	}
};

class Subwoofer : public BaseComponent
{
public:
	string getName() override
	{
		return "Subwoofer";
	}
};

class MusicCenter
{
public:
	vector<BaseComponent*> components;
	void print()
	{
		for (BaseComponent* bc : components) cout << bc->getName() << endl;
	}
};

class BaseBuilder
{
public:
	BaseBuilder() = default;
	virtual void reset() = 0;
	virtual void createDVD() = 0;
	virtual void createRadio() = 0;
	virtual void createSubwoofer() = 0;
	virtual void createBlueray() = 0;

};

class MusicCenterBuilder : public BaseBuilder
{
	MusicCenter* mc;
public:

	MusicCenterBuilder()
	{
		reset();
	}

	void reset() override
	{
		if(mc) delete mc;
		mc = new MusicCenter;
	}

	MusicCenter* getResult() 
	{ 
		MusicCenter* temp = mc;
		mc = new MusicCenter;
		return temp; 
	}

	void createDVD() override
	{
		mc->components.push_back(new DVD);
	}
	void createRadio() override
	{
		mc->components.push_back(new Radio);
	}
	void createSubwoofer() override
	{
		mc->components.push_back(new Subwoofer);
	}
	void createBlueray() override
	{
		mc->components.push_back(new BlueRay);
	}

};

class Director
{
	BaseBuilder* builder;
public:
	Director(BaseBuilder* builder) : builder(builder) {}

	Director(BaseBuilder& builder) : builder(&builder) {}

	void setBuilder(BaseBuilder* builder)
	{
		this->builder = builder;
	}

	void setBuilder(BaseBuilder& builder)
	{
		this->builder = &builder;
	}

	void buildMaxiMC()
	{
		builder->createBlueray();
		builder->createDVD();
		builder->createRadio();
		builder->createSubwoofer();
	}

	void buildMiniMC()
	{
		builder->createRadio();
		builder->createDVD();
	}
};

class Manual
{
	string text = "Manual for MusicCenter\n";
public:

	void addText(string text)
	{
		this->text.append(text);
	}

	void print()
	{
		cout << text << endl;
	}
};

class ManualBuilder : public BaseBuilder
{
	Manual* manual = nullptr;
public:
	ManualBuilder() { reset(); }

	void reset() override
	{
		if(manual) delete manual;
		manual = new Manual;
	}

	void createDVD() override
	{
		manual->addText("To open DVD push on the button with DVD icon, DVD will load automaticly after closing\n");
	}

	void createRadio() override
	{
		manual->addText("To tune radio bla..bla..bla..bla\n");
	}

	void createBlueray() override
	{
		manual->addText("To read blueray bla..bla..bla..bla\n");
	}

	void createSubwoofer() override
	{
		manual->addText("To connect subwoofer just connect subwoofer\n");
	}

	Manual* getResult()
	{
		Manual* temp = manual;
		manual = new Manual;
		return temp;
	}
};