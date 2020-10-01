#pragma once

//---------------------------------------------|
//											   |
//	Str.h     							       |
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

#include <iostream>
#include <locale>
#include <conio.h>
#include <algorithm>

namespace av
{

	class Str
	{
	public:

		char *string = nullptr;

		int length = 0;

		Str();

		Str(Str & obj);

		// ReSharper disable once CppNonExplicitConvertingConstructor
		Str(const char* cha);

		explicit Str(const char _char, const int length);

		explicit Str(const char* cha, const int length);

		explicit Str(Str& str, const int length);

		int size() const;

		static int size(const char* a);

		void append(const char* a);

		void push_back(const char a);

		int find(const char a) const;

		void erase(const int start);

		void erase(int start, int finish);

		void replace(int index, const char* _char);

		void replace(int start, int finish, const char* _char);

		void pop_back(int value = 1);

		void insert(const short index, const char* value);

		Str& toUpper();

		Str& toLower();

		Str& operator=(const char cha);
		
		Str& operator=(const char* cha);

		Str& operator=(const Str &str);

		Str& operator*(const Str &str) const;

		void check();

		void cin(bool secret,bool check, const char* list = nullptr, bool whitelist = false, bool rewrite = true, int min_len = 0, int max_len = 0);

		operator char*() const;

		inline char& operator[](int key) const;

		~Str();

	};

	inline std::ostream& operator<<(std::ostream& os, Str& str)
	{
		os << str.string;
		return os;
	}

	template<class T>
	inline T& operator>>(T& os, Str& str)
	{
		char buff;
		std::cin.get(buff);
		str = buff;
		while (true)
		{
			std::cin.get(buff);
			if (buff == '\n') break;
			str.push_back(buff);
		}
		return os;
	}

	inline bool operator<(const Str& lhs, const Str& rhs);

	inline bool operator>(const Str& lhs, const Str& rhs);

	bool operator== (const Str& lhs, const Str& rhs);

	bool operator==(const Str& lhs, const char* rhs);
}
