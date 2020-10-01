#pragma once

#include <conio.h>
#include <iostream>
#include <vector>
#include <Windows.h>

enum ConsoleColor
{
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    White = 15
};

void SetColor(ConsoleColor text, ConsoleColor background)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((background << 4) | text));
}


void gotoxy(int x, int y)
{
    COORD pos = { x, y };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

template<class T>
class Menu
{
public:
    std::vector<T> _variants;
    int x, y;
    int _choice;

    Menu(std::vector<T> list, int x, int y)
    {
        _variants = list;
        this->x = x;
        this->y = y;
        this->_choice = 0;
    }


    int Enter()
    {
        print();
        while (true)
        {
            int key;
            key = _getch();

            switch (key)
            {
            case 13:
            case 77:
                return _choice;
            case 72:
                if (_choice > 0)
                    _choice--;
                else
                    _choice = _variants.size() - 1;
                break;
            case 80:
                if (_choice < _variants.size() - 1)
                    _choice++;
                else
                    _choice = 0;
                break;
            }
            print();
        }

    }
	
    void print()
    {
        SetColor(LightGray, Black);
        for (auto i = 0; i < _variants.size(); i++)
        {
            gotoxy(x, y + i);
            if (i == _choice)
                SetColor(Black, White);
            else
                SetColor(LightGray, Black);
            std::cout << _variants[i] << std::endl;;
        }
        SetColor(LightGray, Black);
    }

};
