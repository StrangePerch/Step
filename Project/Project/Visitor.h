#pragma once
#include "iostream.h"
#include "fstream.h"

class Visitor;

int distance(int x1, int y1, int x2, int y2)
{
	return abs(sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

class IFigure
{
public:
	virtual void print() = 0;
	virtual void invite(Visitor* visitor) = 0;
};

class Point : public IFigure
{
public:
	int x, y;

	Point(int x, int y) : x(x), y(y) {}
	void print() override
	{
		cout << "Point:" << endl;
		cout << "X = " << x << ", Y = " << y << endl;
	}
	void invite(Visitor* visitor);
};

class Rectangle : public IFigure
{
public:
	int x1, x2, y1, y2;

	Rectangle(int x1, int x2, int y1, int y2) : x1(x1), x2(x2), y1(y1), y2(y2) {}
	void print() override
	{
		cout << "Rectangle:" << endl;
		cout << "X1 = " << x1 << ", Y1 = " << y1 << endl;
		cout << "X2 = " << x2 << ", Y2 = " << y2 << endl;
	}
	void invite(Visitor* visitor);
};

class Triangle : public IFigure
{
public:
	int x1, x2, x3, y1, y2, y3;

	Triangle(int x1, int x2, int x3, int y1, int y2, int y3) : x1(x1), x2(x2), x3(x3), y1(y1), y2(y2), y3(y3) {}
	void print() override
	{
		cout << "Triangle:" << endl;
		cout << "X1 = " << x1 << ", Y1 = " << y1 << endl;
		cout << "X2 = " << x2 << ", Y2 = " << y2 << endl;
		cout << "X3 = " << x3 << ", Y3 = " << y3 << endl;
	}
	void invite(Visitor* visitor);
};

class Visitor
{
public:
	virtual void visit(Point* point) = 0;
	virtual void visit(Rectangle* rectangle) = 0;
	virtual void visit(Triangle* triangle) = 0;
};

class HTML_Export : public Visitor
{
public:
	void visit(Point* p)
	{
		string res = "";
		res += "<table><tr><td>Point</td><td>X=";
		char buff[10];
		_itoa(p->x, buff, 10);
		res += buff;
		res += "</td><td>Y=";
		_itoa(p->y, buff, 10);
		res += buff;
		res += "</td></tr></table>";
		ofstream out("site.html", std::ios::app);
		out << res << endl;
		out.close();
	}
	void visit(Triangle* t)
	{
		string res = "";
		res += "<table><tr><td>Triangle</td><td>P1(";
		char buff[10];
		_itoa(t->x1, buff, 10);
		res += buff;
		res += ", ";
		_itoa(t->y1, buff, 10);
		res += buff;
		res += ")</td><td>P2(";
		_itoa(t->x2, buff, 10);
		res += buff;
		res += ", ";
		_itoa(t->y2, buff, 10);
		res += buff;
		res += ")</td><td>P3(";
		_itoa(t->x3, buff, 10);
		res += buff;
		res += ", ";
		_itoa(t->y3, buff, 10);
		res += buff;
		res += ")</td></tr></table>";
		ofstream out("site.html" , std::ios::app);
		out << res << endl;
		out.close();;
	}
	void visit(Rectangle* r)
	{
		string res = "";
		res += "<table><tr><td>Rectangle</td><td>P1(";
		char buff[10];
		_itoa(r->x1, buff, 10);
		res += buff;
		res += ", ";
		_itoa(r->y1, buff, 10);
		res += buff;
		res += ")</td><td>P2(";
		_itoa(r->x2, buff, 10);
		res += buff;
		res += ", ";
		_itoa(r->y2, buff, 10);
		res += buff;
		res += ")</td></tr></table>";
		ofstream out("site.html", std::ios::app);
		out << res << endl;
		out.close();
	}

};

class TXT_Export : public Visitor
{
public:
	void visit(Point* p)
	{
		string res = "";
		res += "Point X=";
		char buff[10];
		_itoa(p->x, buff, 10);
		res += buff;
		res += ", Y=";
		_itoa(p->y, buff, 10);
		res += buff;
		ofstream out("file.txt", std::ios::app);
		out << res << endl;
		out.close();
	}
	void visit(Triangle* t)
	{
		string res = "";
		res += "Triangle P1(";
		char buff[10];
		_itoa(t->x1, buff, 10);
		res += buff;
		res += ", ";
		_itoa(t->y1, buff, 10);
		res += buff;
		res += "), P2(";
		_itoa(t->x2, buff, 10);
		res += buff;
		res += ", ";
		_itoa(t->y2, buff, 10);
		res += buff;
		res += "), P3(";
		_itoa(t->x3, buff, 10);
		res += buff;
		res += ", ";
		_itoa(t->y3, buff, 10);
		res += buff;
		res += ")";
		ofstream out("file.txt", std::ios::app);
		out << res << endl;
		out.close();;
	}
	void visit(Rectangle* r)
	{
		string res = "";
		res += "Rectangle P1(";
		char buff[10];
		_itoa(r->x1, buff, 10);
		res += buff;
		res += ", ";
		_itoa(r->y1, buff, 10);
		res += buff;
		res += "), P2(";
		_itoa(r->x2, buff, 10);
		res += buff;
		res += ", ";
		_itoa(r->y2, buff, 10);
		res += buff;
		res += ")";
		ofstream out("file.txt", std::ios::app);
		out << res << endl;
		out.close();
	}

};

class Perimetr : public Visitor
{
public:
	
	void visit(Point* p) {}

	void visit(Rectangle* r)
	{
		int w, h;

		w = abs(r->x1 - r->x2);
		h = abs(r->y1 - r->y2);;

		cout << "Rectangle perimetr = " << w * 2 + h * 2 << endl;
	}
	void visit(Triangle* r)
	{
		cout << "Triange perimetr = " << 
			distance(r->x1, r->y1, r->x2, r->y2)
			+ distance(r->x2, r->y2, r->x3, r->y3)
			+ distance(r->x3, r->y3, r->x1, r->y1) 
			<< endl;
	}
};

void Rectangle::invite(Visitor* visitor)
{
	visitor->visit(this);
}

void Point::invite(Visitor* visitor)
{
	visitor->visit(this);
}

void Triangle::invite(Visitor* visitor)
{
	visitor->visit(this);
}
