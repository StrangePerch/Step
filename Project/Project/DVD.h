#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class Write
{
	string file;
public:

	Write(string file) : file(file)
	{}

	void write(string data)
	{
		ofstream out(file);
		out << data;
		out.close();
	}
};

class Read
{
	string file;
public:

	Read(string file) : file(file)
	{}

	int read()
	{
		ifstream in(file);
		string data;
		in >> data;
		hash<string> _hash;
		in.close();
		return _hash(data);
	}
};

class DVD
{
	string file;

	void check_disk(string file)
	{
		if (false)
			throw "disk_corrupted";
	}

	bool check_space()
	{
		return true;
	}

public:

	DVD(string file) : file(file)
	{
		check_disk(file);
	}

	void read()
	{
		Read read(file);
		read.read();
	}

	void write(string data)
	{
		if (!check_space()) throw "no_space";
		hash<string> _hash;
		int sum = _hash(data);
		Write write(file);
		write.write(data);
		Read read(file);
		if (sum == read.read()) cout << "Диск записан" << endl;
		else throw "write_error";
	}
};

/*
int main()
{
setlocale(LC_ALL, "");
try
{
DVD dvd("file.txt");
dvd.write("data");
}
catch (const char* error)
{
cout << error << endl;
}
system("pause");
}
*/