#include <iostream>

#include "../../Str.h"

using namespace av;

using std::cout;
using std::cin;
using std::endl;


int main()
{
	/*
	Str string = "Hello";
	cout << string << endl;
	string = "World";
	cout << string << endl;
	string.insert(0, "Hello");
	cout << string << endl;
	string.insert(5, " ");
	cout << string << endl;
	string.pop_back(5);
	cout << string << endl;
	string.pop_back();
	cout << string << endl;
	string.append(" Step");
	cout << string << endl;
	string.erase(6, 10);
	cout << string << endl;
	string.append("Ukraine");
	cout << string << endl;
	string.replace(15, "and World");
	cout << string << endl;
	string.insert(30, "And me");
	cout << string << endl;
	cout << string.length << endl;
	string.pop_back(5);
	cout << string << endl;
	cout << string.length << endl;
	Str a = string;
	cout << (a == string) << endl;
	cout << (a > string) << endl;
	cout << (a != string) << endl;
	a.pop_back(5);
	cout << a << endl;
	cout << (a == string) << endl;
	cout << (a > string) << endl;
	cout << (a < string) << endl;
	Str b('b', 3);
	cout << b << endl;
	Str c(string, 5);
	cout << c << endl;
	char g[5] = "abcd";
	Str d(g, 2);
	cout << d << endl;
	system("pause");
	*/
	while (true)
	{
		Str a;
		a.cin(true, "123", false);
		system("pause");
		cout << a << endl;
		system("pause");
	}
	system("pause");
}