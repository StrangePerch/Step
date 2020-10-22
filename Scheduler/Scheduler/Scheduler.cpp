#include "Scheduler.h"
#include "Menu.h"

string* _cin()
{
	char temp[80];

	cin.get();
	cin.getline(temp, 80);
	
	return new string(temp);
}

Scheduler::Scheduler()
{
	load();
	check();
}

void Scheduler::save()
{
	ofstream out("save.txt");
	out << sorted_by_date.size() << ' ';
	for (auto temp : sorted_by_date)
	{
		Task task = *temp.second;
		task.save(out);
	}
}

void Scheduler::load()
{
	ifstream in("save.txt");
	int size;
	in >> size;
	for (size_t i = 0; i < size; i++)
	{
		Task* temp = new Task(in);
		add(temp);
	}
}

void Scheduler::add(Task* task)
{
	tasks.insert(make_pair(*task->finish, task));
	sorted_by_date.insert(make_pair(*task->finish, task));
	sorted_by_title.insert(make_pair(task->title, task));
	sorted_by_tag.insert(make_pair(task->tag, task));
	sorted_by_priority.insert(make_pair(task->priority, task));
}

void Scheduler::del(Task* task)
{
	tasks.erase(*task->finish);
	expired.erase(*task->finish);
	sorted_by_date.erase(*task->finish);
	sorted_by_title.erase(task->title);
	sorted_by_tag.erase(task->tag);
}

void Scheduler::sort()
{
	sorted_by_title.clear();
	sorted_by_tag.clear();
	sorted_by_date.clear();
	for (auto task : tasks)
	{
		sorted_by_date.insert(make_pair(*task.second->finish, task.second));
		sorted_by_title.insert(make_pair(task.second->title, task.second));
		sorted_by_tag.insert(make_pair(task.second->tag, task.second));
	}
	for (auto task : expired)
	{
		sorted_by_date.insert(make_pair(*task.second->finish, task.second));
		sorted_by_title.insert(make_pair(task.second->title, task.second));
		sorted_by_tag.insert(make_pair(task.second->tag, task.second));
	}
}

void Scheduler::check()
{
	Date* now = today_full();
	for (auto iter = tasks.begin(); iter != tasks.end(); iter++)
	{
		if (*iter->second->finish < *now)
		{
			expired.insert(make_pair(iter->first, iter->second));
		}
	}
	for (auto task : expired)
	{
		auto it = tasks.find(task.first);
		if(it != tasks.end())
		tasks.erase(it);
	}
}

void Scheduler::print_title()
{
	for (auto task : sorted_by_title)
	{
		std::cout << *task.second << endl;
	}
}

void Scheduler::print_date()
{
	for (auto task : sorted_by_date)
	{
		std::cout << *task.second << endl;
	}
}

void Scheduler::print_tag()
{
	for (auto task : sorted_by_tag)
	{
		std::cout << *task.second << endl;
	}
}

void Scheduler::print()
{
	int counter = 0;

	int first = true;
	
	for (auto task : tasks)
	{
		if (*task.second->start <= *today_full() && *task.second->finish >= *today_full())
		{
			if (first) std::cout << "NOW:" << endl;
			first = false;
			counter++;
			std::cout << "#" << counter << "- " << *task.second << endl;
		}
	}

	first = true;

	counter = 0;
	for (auto task : tasks)
	{
		if (*task.second->start == *today() || *task.second->finish == *today())
		{
			if (first) std::cout << "TODAY:" << endl;
			first = false;
			counter++;
			std::cout << "#" << counter << "- " << *task.second << endl;
		}
	}

	if (tasks.size())
	{
		std::cout << "TASKS:" << endl;
		counter = 0;
		for (auto task : tasks)
		{
			counter++;
			std::cout << "#" << counter << "- " << *task.second << endl;
		}
	}
	else
		if (expired.size()) std::cout << "EVERYTHING EXPIRED NEXT TIME TRY TO DO FASTER" << endl;
		else std::cout << "NO TASKS EXIST" << endl;

	counter = 0;

	if (expired.size())
	{
		std::cout << "EXPIRED:" << endl;
		for (auto task : expired)
		{
			counter++;
			cout << "#" << counter << "- " << *task.second << endl;
		}
	}
	else
	std::cout << "NOTHING EXPIRED" << endl;
}

void Scheduler::colorize(Date& date)
{
	ConsoleColor text_color = LightGray;
	ConsoleColor back_color = Black;;
	if (tasks.count(date))
	{
		back_color = Green;
	}
	else if (expired.count(date))
	{
		back_color = Red;
	}
	else
	{
		back_color = Black;
	}
	
	if (date.getNameOfDay() == "Su" || date.getNameOfDay() == "Sa")
		text_color = Yellow;
	else
		text_color = LightGray;
	if (date == *today())
	{
		text_color = Blue;
	}
	SetColor(text_color, back_color);
}

void Scheduler::calendar(int month, int year, int x, int y)
{
	Date* now = new Date(1, month, year);

	gotoxy(x, y);
	
	std::cout << setw(18) << getNameOfMonth(month, true) << endl;
	
	SetColor(Black, LightGray);

	gotoxy(x, ++y);
	for (size_t i = 0; i < 7; i++)
	{
		cout << setw(3) << getNameOfDay(i) << " ";
	}
	SetColor(LightGray, Black);
	gotoxy(x, ++y);

	int prev = (int)*now->day_of_week();
	int max = getDaysInMonth(now->month - 1, now->year);
	if (prev > 0)
	{
		for (int i = -prev + 1; i <= 0; i++)
		{
			Date temp(max + i, now->month - 1, now->year);
			colorize(temp);
			std::cout << setw(3) << max + i << " ";
		}
	}
	max = getDaysInMonth(now->month, now->year);
	for (size_t i = prev; i < 42; i++)
	{
		if (!(i % 7)) gotoxy(x, ++y);
		int iter;
		bool next;
		if (i - prev + 1 <= max)
		{
			iter = i - prev + 1;
			next = false;
		}
		else
		{
			iter = i - prev + 1 - max;
			next = true;
		}
		Date temp(iter, now->month + next, now->year);
		colorize(temp);
		std::cout << setw(3) << iter << ' ';
	}
	SetColor(LightGray, Black);
	gotoxy(x, ++y);
}

void Scheduler::date_in(Task* task, int x, int y)
{
	int date[12];

	int month, day, year, hour, min;

	bool second = false;
	
	int pos = 0;

	for (size_t i = 0; i < 12; i++)
	{
		date[i] = 0;
	}
	
	while (true)
	{
		gotoxy(x, y);
		for (int i = 0; i < 60; ++i)
		{
			cout << ' ';
		}
		gotoxy(x, y);
		cout << "Date: ";
		if (second) cout << *task->start << " - ";
		for (int i = 0; i < pos; ++i)
		{
			month = date[2] * 10 + date[3];
			day = date[0] * 10 + date[1];
			year = date[4] * 1000 + date[5] * 100 + date[6] * 10 + date[7];
			hour = date[8] * 10 + date[9];
			min = date[10] * 10 + date[11];
			
			if (month > 12)
			{
				month = 12;
				date[2] = 1;
				date[3] = 2;
			}

			int max = getDaysInMonth(month, year);
			
			if(day > max)
			{
				date[0] = max / 10;
				date[1] = max % 10;
			}
			if(hour > 24)
			{
				date[8] = 2;
				date[9] = 4;
			}
			if (min > 59)
			{
				date[10] = 5;
				date[11] = 9;
			}
			if(hour == 24)
			{
				date[10] = 0;
				date[11] = 0;
			}
			if (i == 2 || i == 4) cout << '/';
			if (i == 8) cout << ' ';
			if (i == 10) cout << ':';
			cout << date[i];
		}

		month = date[2] * 10 + date[3];
		day = date[0] * 10 + date[1];
		year = date[4] * 1000 + date[5] * 100 + date[6] * 10 + date[7];
		hour = date[8] * 10 + date[9];
		min = date[10] * 10 + date[11];
		
		int key;
		key = _getch();

		switch (key)
		{
		case '-':
			task->start = new Date(day, month, year, hour, min);
			task->finish = task->start;
			pos = 0;
			second = true;
			break;
		case 13:
		case 77:
			if (pos == 12)
			{
				if (!second)
				{
					task->start = new Date(day, month, year, hour, min);
					task->finish = task->start;
				}
				else
				{
					task->finish = new Date(day, month, year, hour, min);
				}
			}
			return;
		case '\b':
			pos--;
			if (pos < 0)
				if (second)
				{
					second = false;
					pos = 12;
				}
				else pos = 0;
			break;
		default:
			key -= '0';
			if(key >= 0 && key <= 9)
			{
				if (pos < 12)
				{
					date[pos] = key;
					pos++;
				}
			}
			
		}
		
	}
}

void Scheduler::add_menu()
{
	cout << "Title: ";
	string title = *_cin();
	int prior;
	cout << "Priority: ";
	cin >> prior;
	cout << "Tag: ";
	string tag = *_cin();
	cout << "Task: ";
	string task = *_cin();

	Task* temp = new Task(title, task, tag);
	temp->priority = prior;
	
	date_in(temp,0,4);
	
	add(temp);
}

void Scheduler::find_menu()
{
	vector<string> list = {"Title", "Tag", "Date", "Priority", "Exit"};
	Menu<string> main(list, 0, 1);

	while (true)
	{
		cout << "Sort by:";
		switch (main.Enter())
		{
		case 0:
			find_by_title();
			break;
		case 1:
			find_by_tag();
			break;
		case 2:
			find_by_date();
			break;
		case 3:
			find_by_prior();
			break;
		default: return;
		}
	}
}

void Scheduler::find_by_title()
{
	system("cls");

	map<string, Task*>::iterator it;

	while (1)
	{
		int i = 1;

		for (auto temp : sorted_by_title)
		{
			cout << "#" << i << "- " << *temp.second << endl;
			i++;
		}
		cout << "Title: ";
		auto tit = _cin();

		system("cls");

		it = sorted_by_title.find(*tit);
		if (it != sorted_by_title.end()) break;
	}

	task_menu(it->second);
	system("pause");
	system("cls");
}

void Scheduler::find_by_tag()
{
	int choice;
	vector<Task> list;
	map<string, string> tags_map;
	vector<string> tags;

		std::system("cls");

		map<string, Task*>::iterator it;		

		int i = 1;
		cout << "Sorted by tag" << endl;
		tags.clear();
		for (auto temp : sorted_by_tag)
		{
			tags_map.insert(make_pair(temp.second->tag, temp.second->tag));
			cout << "#" << i << "- " << *temp.second << endl;
			i++;
		}

		for (auto t : tags_map)
		{
			tags.push_back(t.second);
		}
		cout << "Tag: ";

		tags.push_back("EXIT");
		
		Menu<string> menu1(tags,0, i + 1);
		choice = menu1.Enter();
		if (choice == tags.size() - 1) return;
		std::system("cls");

		i = 1;

		string tag = tags[choice];
		
		list.clear();

		for (auto temp : sorted_by_tag)
		{
			if (temp.second->tag == tag)
			{
				list.push_back(*temp.second);
				i++;
			}
		}

		//list.push_back("EXIT");
		Menu<Task> menu(list, 0, 0);
		choice = menu.Enter();
		//if (choice != list.size() - 1) break;

	auto fin = sorted_by_title.find(list[choice].title);

	cout << endl << endl;
	
	task_menu(fin->second);
	std::system("pause");
	std::system("cls");
}

void Scheduler::find_by_date()
{
	std::system("cls");

	map<Date, Date*> temp_map;
	vector<Date> list;
	int choice;

		int i = 1;

		for (auto temp : sorted_by_date)
		{
			temp_map.insert(make_pair(*temp.second->finish, temp.second->finish));
			cout << "#" << i << "- " << *temp.second << endl;
			i++;
		}
		
		for (auto t : temp_map)
		{
			list.push_back(*t.second);
		}

		Menu<Date> menu(list, 0, i + 1);
		choice = menu.Enter();
		

	auto fin = sorted_by_date.find(list[choice]);

	cout << endl << endl;
	
	task_menu(fin->second);
	std::system("pause");
	std::system("cls");
}

void Scheduler::find_by_prior()
{
	int choice;
	vector<Task> list;
	map<int, int> prior_map;
	vector<int> prior;

	std::system("cls");

	map<int, Task*>::iterator it;

	int i = 1;
	cout << "Sorted by priority" << endl;
	prior.clear();
	for (auto temp : sorted_by_priority)
	{
		prior_map.insert(make_pair(temp.second->priority, temp.second->priority));
		cout << "#" << i << "- " << *temp.second << endl;
		i++;
	}

	for (auto t : prior_map)
	{
		prior.push_back(t.second);
	}
	cout << "Priority: ";

	Menu<int> menu1(prior, 0, i + 1);
	choice = menu1.Enter();
	std::system("cls");

	i = 1;

	int pri = prior[choice];

	list.clear();

	for (auto temp : sorted_by_priority)
	{
		if (temp.second->priority == pri)
		{
			list.push_back(*temp.second);
			i++;
		}
	}

	//list.push_back("EXIT");
	Menu<Task> menu(list, 0, 0);
	choice = menu.Enter();
	//if (choice != list.size() - 1) break;

	auto fin = sorted_by_title.find(list[choice].title);

	cout << endl << endl;

	task_menu(fin->second);
	std::system("pause");
	std::system("cls");
}

void Scheduler::main_menu()
{
	vector<string> list = {"ShowAll", "AddNew", "Find", "Exit"};
	while (true)
	{
		std::system("cls");
		calendar(today()->month, today()->year, 60, 2);
		Menu<string> main(list, 10, 5);
		check();
		switch (main.Enter())
		{
		case 0:
			system("cls");
			print();
			system("pause");
			break;
		case 1:
			system("cls");
			add_menu();
			break;
		case 2:
			system("cls");
			find_menu();
			break;
		default: return;
		}
	}
}

void Scheduler::edit_menu(Task* task)
{
	while (1)
	{
		system("cls");
		task->print();
		const vector<string> list = { "Title", "Tag", "Date", "Task", "Priority", "EXIT" };
		Menu<string> menu(list, 0, 7);
		int choice = menu.Enter();

		bool l;

		switch (choice)
		{
		case 0:
			system("cls");
			task->print();
			cout << "Title: ";
			cin >> task->title;
			break;
		case 1:
			system("cls");
			task->print();
			cout << "Tag: ";
			cin >> task->tag;
			break;
		case 2:

			system("cls");
			task->print();;
			date_in(task, 0, 8);

			break;
		case 3:
			system("cls");
			task->print();
			cout << "Task: ";
			task->task = *_cin();
			break;
		case 4:
			system("cls");
			task->print();
			cout << "Priority: ";
			cin >> task->priority;
			break;
		default:
			return;
		}
		del(task);
		add(task);
	}
}

void Scheduler::task_menu(Task* task)
{
	system("cls");
	task->print();
	const vector<string> list = {"Check as finished", "Edit", "EXIT"};
	Menu<string> menu(list, 0, 8);
	int choice = menu.Enter();

	switch (choice)
	{
	case 0:
		del(task);
		break;
	case 1:
		edit_menu(task);
		break;
	case 2:
		return;
	}
}
