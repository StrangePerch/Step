#pragma once
#include <iostream>

using namespace std;

class IFigure
{
public:
	virtual IFigure* clone() = 0;
	virtual void print() = 0;
};

class Triangle : public IFigure
{
	int a, b, c;
public:

	Triangle(int a,int b, int c) : a(a), b(b), c(c){}

	IFigure* clone() override
	{
		return new Triangle(a,b,c);
	}

	void print() override
	{
		cout << "Im Triangle a = " << a << ", b = " << b << ", c = " << c << endl;
	}
};

class Square : public IFigure
{
	int a;
public:
	Square(int a) : a(a) {}

	IFigure* clone() override
	{
		return new Square(a);
	}

	void print() override
	{
		cout << "Im Square a = " << a << endl;
	}
};

class Circle : public IFigure
{
	int r;
public:
	Circle(int r) : r(r) {}

	IFigure* clone() override
	{
		return new Circle(r);
	}

	void print() override
	{
		cout << "Im Circle and my radius = " << r << endl;
	}
};