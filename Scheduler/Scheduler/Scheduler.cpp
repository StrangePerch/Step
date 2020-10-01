#include "Scheduler.h"
#include "Menu.h"

string* _cin()
{
	char temp[80];
	
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

	std::cout << "NOW:" << endl;
	for (auto task : tasks)
	{
		if (*task.second->start <= *today_full() && *task.second->finish >= *today_full())
		{
			counter++;
			std::cout << "#" << counter << "- " << *task.second << endl;
		}
	}

	std::cout << "TODAY:" << endl;
	counter = 0;
	for (auto task : tasks)
	{
		if (*task.second->start == *today() || *task.second->finish == *today())
		{
			counter++;
			std::cout << "#" << counter << "- " << *task.second << endl;
		}
	}

	std::cout << "TASKS:" << endl;
	counter = 0;
	for (auto task : tasks)
	{
		counter++;
		std::cout << "#" << counter << "- " << *task.second << endl;
	}

	counter = 0;

	std::cout << "EXPIRED:" << endl;
	for (auto task : expired)
	{
		counter++;
		cout << "#" << counter << "- " << *task.second << endl;
	}
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

void Scheduler::add_menu()
{
	cout << "Title: ";
	string title;
	std::cin >> title;
	cout << "Tag: ";
	string tag;
	std::cin >> tag;
	cout << "Task: ";
	string task;
	std::cin >> task;
	cout << "Long(from, till) or short (at)? (1,0)" << endl;
	bool choice;
	std::cin >> choice;
	Date* date[2];
	for (size_t i = 0; i <= choice; i++)
	{
		cout << "Date #" << i + 1 << endl;
		cout << "Day: ";
		int day;
		std::cin >> day;
		cout << "Month: ";
		int month;
		std::cin >> month;
		cout << "Year: ";
		int year;
		std::cin >> year;
		cout << "Hour: ";
		int hour;
		std::cin >> hour;
		cout << "Minute: ";
		int minute;
		std::cin >> minute;
		date[i] = new Date(day, month, year, hour, minute);
	}
	if (!choice)
		add(new Task(title, task, tag, date[0]));
	else
		add(new Task(title, task, tag, date[0], date[1]));
}

void Scheduler::find_menu()
{
	vector<string> list = {"Title", "Tag", "Date", "Exit"};
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
	system("cls");
	task->print();
	const vector<string> list = {"Title", "Tag", "Date", "Task", "EXIT"};
	Menu<string> menu(list, 0, 8);
	int choice = menu.Enter();

	bool l;

	switch (choice)
	{
	case 0:
		cout << "Title: ";
		cin >> task->title;
		break;
	case 1:
		cout << "Tag: ";
		cin >> task->title;
		break;
	case 2:
		cout << "Date: (From , till), (at) press 0 or 1";
		cin >> l;
		if (l)
		{
			cout << "Date: ";
			cout << "-Day: ";
			int day;
			cin >> day;
			cout << "-Month: ";
			int month;
			cin >> month;
			cout << "-Year: ";
			int year;
			cin >> year;
			Date* temp = new Date(day, month, year);
			task->start = temp;
			task->finish = temp;
		}
		else
		{
			cout << "From: ";
			cout << "-Day: ";
			int day;
			cin >> day;
			cout << "-Month: ";
			int month;
			cin >> month;
			cout << "-Year: ";
			int year;
			cin >> year;
			Date* temp = new Date(day, month, year);
			task->start = temp;
			cout << "Till: ";
			cout << "-Day: ";
			cin >> day;
			cout << "-Month: ";
			cin >> month;
			cout << "-Year: ";
			cin >> year;
			temp = new Date(day, month, year);
			task->finish = temp;
		}

		break;
	case 3:
		cout << "Task: ";
		task->title = *_cin();
		break;
	default:
		return;
	}
	del(task);
	add(task);
}

void Scheduler::task_menu(Task* task)
{
	system("cls");
	task->print();
	const vector<string> list = {"Check as finished", "Edit", "EXIT"};
	Menu<string> menu(list, 0, 5);
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
