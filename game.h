#include "board_rect.h"
#include "player.h"


class game
{
private:
	board *B;
	player *VS[2] ;
public:
	game(int S)
	{
		this->B = new board_square(S);
	}
	
	game(int I, int J)
	{
		this->B = new board_rect(I, J);
	}
	
	~game()
	{
		delete this->B;
		
	}

	void mode(int tumbler)
	{
		switch (tumbler)
		{
			case 1:
				{
					player *_1 = new player(1, Human, X);
					player *_2 = new player(2, Human, O);
					VS[0] = _1;
					VS[1] = _2;
					
					break;
				}
			case 2:
			{
					player *_1 = new player(1, Human, X);
					player *_2 = new player(2, CPU, O);
					VS[0] = _1;
					VS[1] = _2;
					break;
			}
			case 3:
			{
					player *_1 = new player(1, CPU, X);
					player *_2 = new player(2, Human, O);
					VS[0] = _1;
					VS[1] = _2;
					break;
			}
			case 4:
			{
					player *_1 = new player(1, CPU, X);
					player *_2 = new player(2, CPU, O);
					VS[0] = _1;
					VS[1] = _2;
					break;
			}
		}
	}

	int choose_mode()
	{
		int m;
			do
			{
				system("cls");
				cout << "Choose game mode\n1 - Player(X) VS Player(O)\n2 - Player(X) VS CPU(O)\n";
				cout << "3 - Player(O) VS CPU(X)\n4 - CPU(X) VS CPU(0)\n-> ";
				cin.clear ();
				cin.sync ();
				cin >> m;
			} while (cin.fail() || m < 1 || m > 4);
			
			return m;
	}

	void move(player *p)
		{

			switch (p->type)
			{
				case Human:
				{
					while(true)
					{
						try
						{
							cout <<"Player " << p->id << ", make your move!\n->";
							this->B->manual_move(p->id);
							break;

						}
						catch(Invalid_Move &IM)
						{
							IM.Error_Message();
							continue;
						}
					
						catch(Index_Error &IE)
						{
							IE.Error_Message();
							continue;
						}
					}
					break;
				}
				case CPU:
				{
					this->B->cpu_move(p->id, p->fig);
					break;
				}
			}
		}

	void show_board()
	{
		int i;
		system("cls");

		for(i = 0; i < 2; i++)
		{
			this->VS[i]->info();
		}
		this->B->show();
	}

	void run()
	{
		this->mode(choose_mode());
		int i;
		this->show_board();
		while(true)
		{
			for(i = 0; i < 2; i++)
			{
				move(this->VS[i]);
				if (this->B->check_draw() || this->B->check_victory(this->VS[i]->fig))
				{
					return;
				}
				this->show_board();
			}
		}
	}
};