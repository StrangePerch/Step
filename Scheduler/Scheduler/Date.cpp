#include "Date.h"

bool operator<(Date a, Date b)
{
	if (a.year < b.year) return true;
	else if (a.year > b.year) return false;
	if (a.month < b.month) return true;
	else if (a.month > b.month) return false;
	if (a.day < b.day) return true;
	else if (a.day > b.day) return false;
	if (a.time && b.time)
	{
		if (a.time->hour < b.time->hour) return true;
		else if (a.time->hour > b.time->hour) return false;
		if (a.time->min < b.time->min) return true;
		else if (a.time->min > b.time->min) return false;
	}
	return false;
}

bool operator>(Date a, Date b)
{
	if (a.year > b.year) return true;
	else if (a.year < b.year) return false;
	if (a.month > b.month) return true;
	else if (a.month < b.month) return false;
	if (a.day > b.day) return true;
	if (a.time && b.time)
	{
		if (a.time->hour > b.time->hour) return true;
		else if (a.time->hour < b.time->hour) return false;
		if (a.time->min > b.time->min) return true;
		else if (a.time->min < b.time->min) return false;
	}
	return false;
}

bool operator>=(Date a, Date b)
{
	return a > b || a == b;
}

bool operator<=(Date a, Date b)
{
	return a < b || a == b;
}

bool operator==(Date a, Date b)
{
	if (a.year != b.year) return false;
	if (a.month != b.month) return false;
	if (a.day != b.day) return false;
	if (a.time && b.time)
		if (a.time->hour != b.time->hour || a.time->min != b.time->min) return false;
	return true;
}

ostream& operator<<(ostream& os, Date& date)
{
	if (date.day < 10) os << '0';
	os << date.day << "/";
	if (date.month < 10) cout << '0';
	cout << date.month << "/";
	int temp = date.year;
	while (temp < 1000)
	{
		temp *= 10;
		cout << '0';
	}
	cout << date.year;
	if (date.time)
	{
		cout << ' ';
		if (date.time->hour < 10) cout << '0';
		cout << date.time->hour << ':';
		if (date.time->min < 10) cout << '0';
		cout << date.time->min;
	}
	cout << ' ' << date.getNameOfDay();
	return os;
}

Date* today()
{
	Str date(__DATE__);
	date.pop_back(8);
	Str mon = date;

	Month month;

	if (mon == "Sep")
		month = September;
	if (mon == "Nov")
		month = November;
	if (mon == "Oct")
		month = October;
	if (mon == "Dec")
		month = December;
	if (mon == "Jan")
		month = January;
	if (mon == "Feb")
		month = February;
	if (mon == "Mar")
		month = March;
	if (mon == "May")
		month = May;
	if (mon == "Apr")
		month = April;
	if (mon == "Jun")
		month = June;
	if (mon == "Jul")
		month = July;
	if (mon == "Aug")
		month = August;
	int day;
	if(__DATE__[6] == ' ')
		day = (__DATE__[5] - '0');
	else
		day = (__DATE__[4] - '0') * 10 + (__DATE__[5] - '0');
	int year = (__DATE__[7] - '0') * 1000 + (__DATE__[8] - '0') * 100 + (__DATE__[9] - '0') * 10 + (__DATE__[10] - '0');
	return new Date(day, month, year);
}

Date* today_full()
{
	Date* date = today();
	date->time =
		new Date::Time((__TIME__[0] - '0') * 10 + (__TIME__[1] - '0'), (__TIME__[3] - '0') * 10 + (__TIME__[4] - '0'));
	return date;
}

int getDaysInMonth(int _mon, int year)
{
	Month mon = Month(_mon);
	switch (mon)
	{
	case January:
		return 31;
		break;
	case February:
		if (isYearLeap(year)) return 29;
		return 28;
		break;
	case March:
		return 31;
		break;
	case April:
		return 30;
		break;
	case May:
		return 31;
		break;
	case June:
		return 30;
		break;
	case July:
		return 31;
		break;
	case August:
		return 31;
		break;
	case September:
		return 30;
		break;
	case October:
		return 31;
		break;
	case November:
		return 30;
		break;
	case December:
		return 31;
		break;
	default:
		return 31;
	}
}

Date::Time::Time(ifstream& in)
{
	load(in);
}

void Date::Time::save(ofstream& out)
{
	out << 1 << ' ' << hour << ' ' << min << ' ';
}

void Date::Time::load(ifstream& in)
{
	in >> hour >> min;
}

void Date::save(ofstream& out)
{
	out << day << ' ' << month << ' ' << year << ' ';
	if (time)
		time->save(out);
	else
	{
		out << 0;
	}
}

void Date::load(ifstream& in)
{
	int temp;
	in >> day;
	in >> temp;
	in >> year;
	month = Month(temp);
	in >> temp;
	if (temp)
		time = new Time(in);
	else
		time = nullptr;
}

Date::Date(ifstream& in)
{
	load(in);
}

Date::Date(int day, int month, int year, int hour, int min)
{
	this->day = day;
	this->month = Month(month);
	this->year = year;
	check();
	time = new Time(hour, min);
}

Date::Date(int day, Month month, int year, int hour, int min)
{
	this->day = day;
	this->month = Month(month);
	this->year = year;
	check();
	time = new Time(hour, min);
}

Date::Date(int day, Month month, int year)
{
	this->day = day;
	this->month = month;
	this->year = year;
	check();
}

Date::Date(int day, int month, int year)
{
	this->day = day;
	this->month = Month(month);
	this->year = year;
	check();
}

Str getNameOfDay(DayOfWeek* day, bool full)
{
	if (full)
	{
		switch (*day)
		{
		case Mo:
			return "Monday";
			break;
		case Tu:
			return "Tuesday";
			break;
		case We:
			return "Wednesday";
			break;
		case Th:
			return "Thursday";
			break;
		case Fr:
			return "Friday";
			break;
		case Sa:
			return "Saturday";
			break;
		case Su:
			return "Sunday";
			break;
		default:
			break;
		}
	}
	else
	{
		switch (*day)
		{
		case Mo:
			return "Mo";
			break;
		case Tu:
			return "Tu";
			break;
		case We:
			return "We";
			break;
		case Th:
			return "Th";
			break;
		case Fr:
			return "Fr";
			break;
		case Sa:
			return "Sa";
			break;
		case Su:
			return "Su";
			break;
		default:
			break;
		}
	}
}

Str getNameOfDay(int day, bool full)
{
	return getNameOfDay(new DayOfWeek(DayOfWeek(day)), full);
}

Str getNameOfMonth(int month, bool full)
{

	if (full)
	{
		switch (month)
		{
		case January:
			return "January";
			break;
		case February:
			return "February";
			break;
		case March:
			return "March";
			break;
		case April:
			return "April";
			break;
		case May:
			return "May";
			break;
		case June:
			return "June";
			break;
		case July:
			return "July";
			break;
		case August:
			return "August";
			break;
		case September:
			return "September";
			break;
		case October:
			return "October";
			break;
		case November:
			return "November";
			break;
		case December:
			return "December";
			break;
		default:
			throw "Month out of range";
		}
	}
	else
	{
		switch (month)
		{
		case January:
			return "Jan";
			break;
		case February:
			return "Feb";
			break;
		case March:
			return "Mar";
			break;
		case April:
			return "Apr";
			break;
		case May:
			return "May";
			break;
		case June:
			return "Jun";
			break;
		case July:
			return "Jul";
			break;
		case August:
			return "Aug";
			break;
		case September:
			return "Sep";
			break;
		case October:
			return "Oct";
			break;
		case November:
			return "Nov";
			break;
		case December:
			return "Dec";
			break;
		default:
			throw "Month out of range";
		}
	}
}

bool isYearLeap(int y)
{
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) return true;
	return false;
}

int getDaysInMonth(Month mon, int year)
{
	switch (mon)
	{
	case January:
		return 31;
		break;
	case February:
		if (isYearLeap(year)) return 29;
		return 28;
		break;
	case March:
		return 31;
		break;
	case April:
		return 30;
		break;
	case May:
		return 31;
		break;
	case June:
		return 30;
		break;
	case July:
		return 31;
		break;
	case August:
		return 31;
		break;
	case September:
		return 30;
		break;
	case October:
		return 31;
		break;
	case November:
		return 30;
		break;
	case December:
		return 31;
		break;
	default:
		throw "Month out of range";
	}
}

Str Date::getNameOfMonth(bool full)
{
	return ::getNameOfMonth(month, full);
}

Month& Date::check_month()
{
	while (month > 12)
	{
		year++;
		month = Month(month - 12);
	}
	while (month < 1)
	{
		year--;
		month = Month(month + 12);
	}
	return month;
}

Str Date::getNameOfDay(bool full)
{
	return ::getNameOfDay(day_of_week(), full);
}

void Date::check_day()
{
	int max_days = getDaysInMonth(month, year);
	while (day > max_days)
	{
		max_days = getDaysInMonth(month, year);
		day -= max_days;
		month = Month(1 + month);
		if (month > 12)
		{
			year++;
			month = Month(1);
		}
	}
	while (day < 1)
	{
		month = Month(month - 1);
		if (month < 1)
		{
			year--;
			month = Month(12);
			max_days = getDaysInMonth(month, year);
			day = max_days;
		}
		else
		{
			max_days = getDaysInMonth(month, year);
			day = max_days;
		}
	}
}

int Date::get_month_code()
{
	switch (month)
	{
	case January:
		return 1;
		break;
	case February:
		return 4;
		break;
	case March:
		return 4;
		break;
	case April:
		return 0;
		break;
	case May:
		return 2;
		break;
	case June:
		return 5;
		break;
	case July:
		return 7;
		break;
	case August:
		return 3;
		break;
	case September:
		return 6;
		break;
	case October:
		return 1;
		break;
	case November:
		return 4;
		break;
	case December:
		return 6;
		break;
	default:
		break;
	}
}

int Date::get_year_code()
{
	if (isYearLeap(year) && today()->month > February) return (6 + (year % 100) + (year % 100 / 4) - 1) % 7;
	return (6 + (year % 100) + (year % 100 / 4)) % 7;
}

DayOfWeek* Date::day_of_week()
{
	return new DayOfWeek(DayOfWeek((day + get_month_code() + get_year_code()) % 7));
}

void Date::check()
{
	check_month();
	check_day();
}

Date Date::operator++(int)
{
	day++;
	check();
	return *this;
}

Date Date::operator--(int)
{
	day--;
	check();
	return *this;
}

void Date::print()
{
	cout << "Day: ";
	if (day < 10) cout << '0';
	cout << day << ", Month: ";
	cout << getNameOfMonth(true) << ", Year: ";
	int temp = year;
	while (temp < 1000)
	{
		temp *= 10;
		cout << '0';
	}
	cout << year;
	if (time)
	{
		cout << ' ';
		if (time->hour < 10) cout << '0';
		cout << time->hour << ':';
		if (time->min < 10) cout << '0';
		cout << time->min;
	}
	cout << ' ' << getNameOfDay(true);
	cout << endl;
}
