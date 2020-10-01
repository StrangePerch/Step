#include "Str.h"


//---------------------------------------------|
//											   |
//	Str.cpp    							       |
//											   |
//	Not std String library					   |
//											   |
//	Created by:								   |
//											   |
//	Vavilov Aleksandr Aleksandrovich		   |
//											   |
//	© 2020 NONAME corp. All rights reserved	   |
//											   |
//---------------------------------------------|

using namespace  av;

Str::Str() = default;

Str::Str(Str& obj)
{
	try
	{
		auto s = size(obj);
		delete[] string;
		length = s;
		string = new char[++s];
		for (auto i = 0; i < s + 1; i++)
		{
			string[i] = obj.string[i];
		}
	}
	catch (std::bad_alloc & error)
	{
		std::cerr << "bad_alloc caught, not enough memory: " << error.what() << std::endl;
		throw;
	}
}

Str::Str(const char* cha)
{
	try
	{
		length = size(cha);
		string = new char[length + 1];
		for (int i = 0; i < length + 1; i++)
		{
			string[i] = cha[i];
		}
	}
	catch (std::bad_alloc & error)
	{
		std::cerr << "bad_alloc caught, not enough memory: " << error.what() << std::endl;
		throw;
	}
}

Str::Str(const char _char, const int length)
{
	try
	{
		this->length = length;
		string = new char[length + 1];
		for (auto i = 0; i < length; i++)
		{
			string[i] = _char;
		}
		string[length] = '\0';
	}
	catch (std::bad_alloc & error)
	{
		std::cerr << "bad_alloc caught, not enough memory: " << error.what() << std::endl;
		throw;
	}
}

Str::Str(const char* cha, const int length)
{
	try
	{
		this->length = length;
		string = new char[length + 1];
		for (auto i = 0; i < length + 1; i++)
		{
			string[i] = cha[i];
		}
		string[length] = '\0';
	}
	catch (std::bad_alloc & error)
	{
		std::cerr << "bad_alloc caught, not enough memory: " << error.what() << std::endl;
		throw;
	}
}

Str::Str(Str& str, const int length)
{
	try
	{
		this->length = length;
		delete[] string;
		string = new char[length + 1];
		for (auto i = 0; i < length; i++)
		{
			string[i] = str.string[i];
		}
		string[length] = '\0';
	}
	catch (std::bad_alloc & error)
	{
		std::cerr << "bad_alloc caught, not enough memory: " << error.what() << std::endl;
		throw;
	}
}

int Str::size() const
{
	return length;
}

int Str::size(const char* a)
{
	int i = 0;
	while (a[i] != '\0') i++;
	return i;
}

void Str::append(const char* a)
{
	try
	{
		length = size() + size(a);

		auto* temp = new char[length + 1];

		for (auto i = 0; i < size(string); i++)
		{
			temp[i] = string[i];
		}
		for (auto i = size(string); i < length + 1; i++)
		{
			temp[i] = a[i - size(string)];
		}
		delete[] string;
		string = temp;
	}
	catch (std::bad_alloc & error)
	{
		std::cerr << "bad_alloc caught, not enough memory: " << error.what() << std::endl;
		throw;
	}
}

void Str::push_back(const char a)
{
	try
	{
		if (length != 0)
		{
			length++;
			auto* temp = new char[length + 1];
			for (auto i = 0; i <= length - 2; i++)
			{
				temp[i] = string[i];
			}
			temp[length - 1] = a;
			temp[length] = '\0';
			delete[] string;
			string = temp;
		}
		else
		{
			length = 1;
			string = new char[length + 1];
			string[0] = a;
			string[1] = '\0';
		}
	}
	catch (std::bad_alloc & error)
	{
		std::cerr << "bad_alloc caught, not enough memory: " << error.what() << std::endl;
		throw;
	}
}

int Str::find(const char a) const
{
	for (auto i = 0; i < length; i++)
	{
		if(string[i] == a)
		{
			return i;
		}
	}
	return -1;
}

void Str::insert(short index, const char* value)
{
	if (index < 0) throw std::exception("ERROR: Str insert index < 0");

	try
	{
		const auto value_s = size(value);
		length += value_s;

		for (auto i = 0; i < index; i++)
		{
			if (i >= size(string))
			{
				length++;
			}
		}

		auto* temp = new char[length + 1];

		for (auto i = 0; i < index; i++)
		{
			if (i < size(string))
			{
				temp[i] = string[i];
			}
			else
			{
				temp[i] = ' ';
			}
		}
		for (auto i = index; i < value_s + index; i++)
		{
			temp[i] = value[i - index];
		}
		for (auto i = index + value_s; i < length + 1; i++)
		{
			temp[i] = string[i - value_s];
		}
		temp[length] = '\0';
		delete[] string;
		string = temp;
	}
	catch (std::bad_alloc& error)
	{
		std::cerr << "bad_alloc caught, not enough memory: " << error.what() << std::endl;
		throw;
	}
}

Str& Str::toUpper()
{
	for (auto i = 0; i < length; i++)
	{
		if (std::islower(string[i], std::locale()))
		{
			string[i] = std::toupper(string[i], std::locale());
		}
	}
	return *this;
}

Str& Str::toLower()
{
	for (auto i = 0; i < length; i++)
	{
		if (std::isupper(string[i], std::locale()))
		{
			string[i] = std::tolower(string[i], std::locale());
		}
	}
	return *this;
}

void Str::erase(const int start)
{
	erase(start, start);
}

void Str::erase(int start, int finish)
{

	if (start < 0) throw std::exception("ERROR: Str erase start < 0");
	if (finish < 0) throw std::exception("ERROR: Str erase finish < 0");
	if (start >= length) throw std::exception("ERROR: Str erase start >= length");
	if (finish >= length) throw std::exception("ERROR: Str erase finish >= length");
	if (start > finish) throw std::exception("ERROR: Str erase start > finish");
	length += (start - finish) - 1;
	
	auto* temp = new char[length + 1];
	auto a = 0;
	for (auto i = 0; i < start; i++)
	{
		temp[i] = string[i];
		a++;
	}
	for (auto i = finish + 1; i < size(string) + 1; i++)
	{
		temp[a] = string[i];
		a++;
	}
	temp[length] = '\0';
	delete[] string;
	string = temp;
}

void Str::replace(int index, const char* _char)
{
	replace(index, index + size(_char) - 1, _char);
}

void Str::replace(int start, int finish, const char* _char)
{
	if (start < 0) throw std::exception("ERROR: Str replace start < 0");
	if (finish < 0) throw std::exception("ERROR: Str replace finish < 0");
	if (start >= length) throw std::exception("ERROR: Str replace start >= length");
	if (finish >= length) throw std::exception("ERROR: Str replace finish >= length");
	if (start > finish) throw std::exception("ERROR: Str replace start > finish");
	if (finish >= length)
	{
		length += (finish - length) + 1;
		char* temp = new char[length + 1];

		for (int i = 0; i < start; i++)
		{
			if (i < size(string))
			{
				temp[i] = string[i];
			}
			else
			{
				temp[i] = ' ';
			}

		}
		for (int i = 0; i <= finish - start + 1; i++)
		{
			if (i > size(_char)) temp[start + 1] = ' ';
			temp[start + i] = _char[i];
		}
		temp[finish + 1] = '\0';
		delete[] string;
		string = temp;
	}
	else
	{
		for (auto i = 0; i < finish - start + 1; i++)
		{
			string[start + i] = _char[i];
		}
	}
}

void Str::pop_back(int value)
{
	if (value > length) value = length;
	length -= value;
	char* temp = new char[length + 1];
	for (int i = 0; i < length; i++)
	{
		temp[i] = string[i];
	}
	temp[length] = '\0';
	delete[] string;
	string = temp;
}

Str& Str::operator= (const char cha)
{
	length = 1;
	delete[] string;
	string = new char[2];
	string[0] = cha;
	string[1] = '\0';
	return *this;
}

Str& Str::operator= (const char* cha)
{
	length = size(cha);
	delete[] string;
	string = new char[1 + length];
	for (auto i = 0; i <= length; i++)
	{
		string[i] = cha[i];
	}
	return *this;
}

Str& Str::operator= (const Str &str)
{
	length = size(str);
	delete[] string;
	string = new char[1 + length];
	for (auto i = 0; i <= length; i++)
	{
		string[i] = str.string[i];
	}
	return *this;
}

Str& Str::operator*(const Str& str) const
{
	Str temp;
	int max;
	int min;
	if(length >= str.length)
	{
		max = length;
		min = str.length;
	}
	else
	{
		min = length;
		max = str.length;
	}
	for (auto i = 0; i < max; i++)
	{
		for (auto j = 0; j < min; j++)
		{
			if (length >= str.length)
			{
				if (string[i] == str[j])
				{
					if(temp.find(string[i]) == -1)
					temp.push_back(string[i]);
				}
			}
			else
			{
				if (string[j] == str[i])
				{
					if(temp.find(string[j]) == -1)
					temp.push_back(string[j]);
				}
			}
		}
	}
	return temp;
}

void Str::check()
{
	for (int i = 0; i < size(); ++i)
	{
		if (i < size() - 2)
		{
			if (string[i] == '\\')
			{

				if (string[i + 1] == '\\')
				{
					string[i] = '\\';
					erase(i + 1);
				}
				else if (string[i + 1] == 't')
				{
					string[i] = '\t';
					erase(i + 1);
				}
				else if (string[i + 1] == 'n')
				{
					string[i] = '\n';
					erase(i + 1);
				}
			}
		}
	}
}

void Str::cin(bool secret, bool check, const char* list, bool whitelist, bool rewrite, int min_len, int max_len)
{
	if (rewrite)
	{
		delete string;
		length = 0;
	}
	while (true)
	{
		char temp;
		temp = _getch();
		if (temp == '\r')
		{
			if (length >= min_len && (length <= max_len || max_len == 0)) break;
		}
		else if (temp == '\b')
		{
			if (length != 0)
			{
				std::cout << '\b' << ' ' << '\b';
				if (string[size() - 1] == '\n')
				{
					std::system("cls");
					pop_back();
					std::cout << string;
				}
				else if (string[size() - 1] == '\t')
				{
					std::system("cls");
					pop_back();
					std::cout << string;
				}
				else pop_back();
			}
		}
		else if (check && temp == '\\')
		{
			std::cout << " Commands: n - new line, \\ - type \\, t - tab, Choose:";
			temp = _getch();
			for (int i = 0; i < 53; ++i)
			{
				std::cout << "\b \b";
			}
			if (temp == 'n') temp = '\n';
			else if (temp == 't') temp = '\t';
			else temp = '\\';
			std::cout << temp;
			push_back(temp);
		}
		else if (list != nullptr && (length < max_len || max_len == 0))
		{
			bool a = true;
			for (int i = 0; i < size(list); ++i)
			{
				if (list[i] == temp)
				{
					if (whitelist)
					{
						if (!secret)
							std::cout << temp;
						else
							std::cout << '*';
						push_back(temp);
						break;
					}
					else
					{
						a = false;
					}
				}
			}
			if (a && !whitelist)
			{
				std::cout << temp;
				push_back(temp);
			}
		}
		else if (length < max_len || max_len == 0)
		{
			if (!secret)
				std::cout << temp;
			else
				std::cout << '*';
			push_back(temp);
		}
	}

	std::cout << '\n';
}

Str::operator char*() const
{
	char *temp = new char[size() + 1];
	for (auto i = 0; i < size() + 1; i++)
	{
		temp[i] = string[i];
	}
	return temp;
}

char& Str::operator[](const int key) const
{
	return string[key];
}

Str::~Str()
{
	delete[] string;
}

bool av::operator<(const Str& lhs, const Str& rhs)
{
	for (auto i = 0; i < std::min(lhs.size(), rhs.size()); i++)
	{
		if (std::toupper(lhs[i], std::locale()) != std::toupper(rhs[i], std::locale()))
		{
			if (static_cast<int>(std::toupper(lhs[i], std::locale()) < std::toupper(rhs[i], std::locale())))
			{
				return true;
			}
			return false;
		}
	}
	return rhs.size() < lhs.size();
}

bool av::operator>(const Str& lhs, const Str& rhs)
{
	for (auto i = 0; i < std::min(lhs.size(), rhs.size()); i++)
	{
		if (std::toupper(lhs[i], std::locale()) != std::toupper(rhs[i], std::locale()))
		{
			if (static_cast<int>(std::toupper(lhs[i], std::locale()) > std::toupper(rhs[i], std::locale())))
			{
				return true;
			}
			return false;
		}
	}
	return rhs.size() > lhs.size();
}


bool av::operator==(const Str& lhs, const Str& rhs)
{
	if (rhs.size() == lhs.size())
	{
		for (auto i = 0; i < rhs.size(); i++)
		{
			if (lhs[i] != rhs[i]) return false;
		}
		return true;
	}
	return false;
}

bool av::operator==(const Str& lhs, const char* rhs)
{
	if (lhs.size() == Str::size(rhs))
	{
		for (int i = 0; i < Str::size(rhs); i++)
		{
			if (lhs[i] != rhs[i]) return false;
		}
		return true;
	}
	return false;
}
