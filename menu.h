#include "game.h"

class menu
{ 
	friend class game;
private:
	bool run_;
	game * game_;
public:
	menu() 
	{
		this->run_ = true;
	}
	~menu()
	{
		delete this->game_;
	}

	bool select_mode()
	{
		int flag;
		
		cout << "1 - Square matrix\n2 - Rectangular matrix\n->";
		do
		{
			cin.clear();
			cin.sync();
			cin >> flag;
		} while (cin.fail() || flag <= 0 || flag > 2);
		
		switch(flag) 
		{
			
			case 1:
			{
				return true;
				break;
			}
			case 2: 
			{
				return false;
				break;
			}
		}
		return true;
	}

	void new_game()
	{
		if (select_mode())
		{
			int size;
			do
				{
					cout << "Enter size of matrix:\n->";
					cin.clear ();
					cin.sync ();
					cin >> size;
				} while (cin.fail() || size <= 0);
			game_ = new game(size);
		}
		else
		{
			int i_size, j_size;
			do
			{
				cout << "Enter horisontal size of matrix:\n->";
				cin.clear ();
				cin.sync ();
				cin >> j_size;
			} while (cin.fail() || j_size <= 0);
			do
			{
				cout << "Enter vertical size of matrix:\n->";
				cin.clear ();
				cin.sync ();
				cin >> i_size;
			} while (cin.fail() || i_size <= 0);
			game_ = new game(i_size, j_size);
		}
	}

	void run()
	{
		int flag;
		while(run_)
		{
			cout << "		MENU\n";
			cout << "1. New Game\n";
			cout << "2. Exit\n->";
			do
			{
				cin.clear ();
				cin.sync ();
				cin >> flag;
			} while (cin.fail() || (flag > 2) || (flag < 1));

			switch(flag) 
			{
				case 1:
				{
					system("cls");
					this->new_game();
					this->game_->run();
					system("cls");
					break;
				}
				case 2: 
				{
					this->run_ = false;
					break;
				}
			}
		}
		return;
	}
};