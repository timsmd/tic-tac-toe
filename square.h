#include <iostream>
#include <windows.h>

#undef NULL

using namespace std;

enum val 
{
	NULL, 
	X, 
	O
};

struct square
{
	val val_;

	void show_s(int pos)
	{
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 

		switch (val_)
		{
		case 0:
			{
				cout << pos + 1;
				break;
			}
		case 1:
			{
				if (pos / 9 != 0)
					cout << " ";
				SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << "X";
				SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				break;
			}
		case 2:
			{
				if (pos / 9 != 0)
					cout << " ";
				SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << "O";
				SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				break;
			}
		}
	}
	void show_s(int pos_i, int pos_j)
	{
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 

		switch (val_)
		{
		case 0:
			{
				cout << pos_i + 1 << ':' << pos_j + 1;
				break;
			}
		case 1:
			{
				if (pos_i / 9 != 0)
					cout << " ";
				if (pos_j / 9 != 0)
					cout << " ";

				SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << " X ";
				SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				break;
			}
		case 2:
			{
				if (pos_i / 9 != 0)
					cout << " ";
				if (pos_j / 9 != 0)
					cout << " ";

				SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << " O ";
				SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				break;
			}
		}
	}

};

	inline bool operator ==(square &left, square &right)
	{
		if(left.val_ == right.val_)
			return true;
		else 
			return false;
	}