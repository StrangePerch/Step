#pragma once
#include "Date.h"
#include <fstream>
using namespace std;

class Task
{
public:
	Date* start;
	Date* finish;
	string title;
	string tag;
	string task;

	Task(ifstream& in)
	{
		load(in);
	}

	void saveStr(ofstream& out, string& str)
	{
		out << str << " } ";
	}

	void loadStr(ifstream& in, string& str)
	{
		string temp;
		while(true)
		{
			in >> temp;
			if (temp == "}")
			{
				str.pop_back();
				return;
			}
			str.append(temp);
			str.push_back(' ');
		}
	}
	
	
	void save(ofstream& out)
	{
		saveStr(out, title);
		saveStr(out, task);
		saveStr(out, tag);
		start->save(out);
		finish->save(out);
		out << endl;
	}

	void load(ifstream& in)
	{
		loadStr(in,title);
		loadStr(in, task);
		loadStr(in, tag);
		start = new Date(in);
		finish = new Date(in);
	}

	//One day task
	Task(string title, string task, string tag, Date* start)
	{
		this->title = title;
		this->task = task;
		this->start = start;
		this->finish = start;
		this->tag = tag;
	}

	//Long task
	Task(string title, string task, string tag, Date* start, Date* finish)
	{
		this->title = title;
		this->task = task;
		this->tag = tag;
		this->start = start;
		this->finish = finish;
		if (*start > *finish)
		{
			Date* temp = this->start;
			this->start = this->finish;
			this->finish = temp;
			temp = nullptr;
		}
	}

	void print()
	{
		cout << "Title: " << title << endl;
		if (start == finish)
		{
			cout << "Date: " << *start << endl;
		}
		else
		{
			cout << "Date: " << *start << " - " << *finish << endl;
		}

		cout << "Task: " << task << endl;

		cout << "Expired? - ";
		if (*finish < *today()) cout << "true" << endl;
		else cout << "false" << endl;
		cout << "------------------------" << endl;
	}

	friend ostream& operator<< (ostream& os, Task& task)
	{
		os << task.title << " " << task.tag;
		if (task.start != task.finish)
			os << " from " << *task.start << " till " << *task.finish;
		else
			os << " at " << *task.start;
		return os;
	}
	
};