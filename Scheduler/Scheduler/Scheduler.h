#pragma once

#include <iomanip>
#include <map>
#include "Task.h"
#include "Include/Singleton/Singleton.h"
#include <fstream>
#include <vector>


using namespace std;

string* _cin();

class Scheduler : public Singleton<Scheduler>
{
public:
	map <Date, Task*> tasks;
	map <Date, Task*> expired;

	map <string, Task*> sorted_by_title;
	multimap <string, Task*> sorted_by_tag;
	map <Date, Task*> sorted_by_date;

	Scheduler();

	void save();

	void load();

	void add(Task* task);

	void del(Task* task);

	void sort();

	void check();

	void print_title();

	void print_date();

	void print_tag();

	void print();

	void colorize(Date& date);

	void calendar(int month, int year, int x, int y);

	void add_menu();

	void find_menu();

	void find_by_title();

	void find_by_tag();

	void find_by_date();

	void main_menu();

	void edit_menu(Task* task);

	void task_menu(Task* task);
};
