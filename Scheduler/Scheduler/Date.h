#pragma once

#include <iostream>
#include "Include/String/Str.h"
#include <fstream>

using namespace std;

enum Month 
{ January = 1, February, March, April, May, June, July, August, September, October, November, December };

enum DayOfWeek
{
	Su = 0, Mo, Tu, We, Th, Fr, Sa
};

using av::Str;

bool isYearLeap(int y);

int getDaysInMonth(Month mon, int year);

int getDaysInMonth(int mon, int year);

class Date
{
public:
	int day;
	Month month;
	int year;

	struct Time
	{
		int min;
		int hour;

		Time(ifstream& in);

		Time(int hour, int min) : min(min), hour(hour) {}

		void save(ofstream& out);

		void load(ifstream& in);
	};

	Time* time = nullptr;


	void save(ofstream& out);

	void load(ifstream& in);

	Date(ifstream& in);

	Date(int day, Month month, int year);

	Date(int day, int month, int year);

	Date(int day, Month month, int year, int hour, int min);

	Date(int day, int month, int year, int hour, int min);

	Str getNameOfMonth(bool full = false);

	Month& check_month();

	Str getNameOfDay(bool full = false);

	void check_day();

	int get_month_code();

	int get_year_code();

	DayOfWeek* day_of_week();

	void check();

	Date operator++(int);

	Date operator--(int);

	void print();

	friend bool operator<(Date a, Date b);

	friend bool operator>(Date a, Date b);

	friend bool operator>=(Date a, Date b);

	friend bool operator<=(Date a, Date b);

	friend bool operator==(Date a, Date b);

	friend ostream& operator<< (ostream& os, Date& date);
};


Date* today();

Date* today_full();

Str getNameOfDay(DayOfWeek* day, bool full = false);

Str getNameOfDay(int day, bool full = false);

Str getNameOfMonth(int month, bool full = false);
