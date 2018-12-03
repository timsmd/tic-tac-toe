#include "board_square.h"

class board_rect: public board
{
private:
	int i_size, j_size;
	square** matrix;
	
	bool check_dia();
	int scan_row(int k, val type);
	int scan_collumn(int k, val type);
	bool check_row(int j);
	bool check_column(int i);
	bool check_hor_line(int j);
	bool check_vert_line(int i);

public:
	board_rect(int i_, int j_);
	~board_rect();
	void cpu_move(int player_id, val type);
	bool manual_move(int player_id);
	void show();
	bool check_victory(int player_id);
	bool check_draw();
};

	board_rect::board_rect(int i_, int j_)
	{
		int i, j;
		this->i_size = i_;
		this->j_size = j_;

		matrix = new square* [this->i_size];
		
		for (i = 0; i < i_size; i++)
		{
			for(j = 0; j < this->j_size; j++)
			{
				matrix[i] = new square [this->j_size];
			}
		}

		for (i = 0; i < i_size; i++)
		{
			for (j = 0; j < j_size; j++)
			{
				this->matrix[i][j].val_= NULL;
			}
		}
	};	

	board_rect::~board_rect()
	{
		for (int i = 0; i < i_size; i++)
		{
			delete this->matrix[i];
		}
	};

	//------------------
	int board_rect::scan_row(int k, val type)
	{
		int i, j, null_count = 0, type_count = 0, opon_count = 0;
		square **temp;

		temp = new square* [this->i_size];
		
		for (i = 0; i < i_size; i++)
		{
			for(j = 0; j < this->j_size; j++)
			{
				temp[j] = new square [this->j_size];
			}
		}

		temp = this->matrix;

		for (j = 0; j < this->j_size; j++)
		{
			if (temp[k][j].val_ == NULL)
			{
				null_count++;
				opon_count -= 5;
			}
			if (temp[k][j].val_ == type)
			{
				type_count++;
				opon_count = -1000;
			}
			if (temp[k][j].val_ != NULL && temp[k][j].val_ != type)
			{
				type_count = 0;
				null_count = 0;
				opon_count += 100;
			}
		}
		return (null_count + type_count * 4 + opon_count * 5);
	};

	int board_rect::scan_collumn(int k, val type)
	{
		int i, j, null_count = 0, type_count = 0, opon_count = 0;
		square **temp;

		temp = new square* [this->i_size];
		
		for (i = 0; i < i_size; i++)
		{
			for(j = 0; j < this->j_size; j++)
			{
				temp[j] = new square [this->j_size];
			}
		}

		temp = this->matrix;

		for (i = 0; i < this->i_size; i++)
		{
			if (temp[i][k].val_ == NULL)
			{
				null_count++;
				opon_count -= 5;
			}
			if (temp[i][k].val_ == type)
			{
				type_count++;
				opon_count = -1000;
			}
			if (temp[i][k].val_ != NULL && temp[i][k].val_ != type)
			{
				type_count = 0;
				null_count = 0;
				opon_count += 100;
			}
		}
		return (null_count + type_count * 4 + opon_count * 5);
	};
	//------------------

	void board_rect::cpu_move(int player_id, val type)
	{
		int **mat; 
		int i, j;
		
		square **temp;
		temp = new square* [this->i_size];
		for (i = 0; i < i_size; i++)
		{
			for(j = 0; j < this->j_size; j++)
			{
				temp[j] = new square [this->j_size];
			}
		}
		
		temp = this->matrix;
			
		mat = new int* [this->i_size];
		
		for (i = 0; i < this->i_size; i++)
		{
			for(j = 0; j < this->j_size; j++)
			{
				mat[j] = new int [this->j_size];
			}
		}
		
		for (i = 0; i < this->i_size; i++)
		{
			for(j = 0; j < this->j_size; j++)
			{
				mat[i][j] = 0;
			}
		}
		

		for (i = 0; i < this->i_size; i++)
		{
			for(j = 0; j < this->j_size; j++)
			{
				mat[i][j] += scan_row(i, type) + scan_collumn(j, type);
			}
		}

	
		
		for(i = 0; i < this->i_size; i++)
		{
			for(j = 0; j < this->j_size; j++)
			{
				if (temp[i][j].val_ != NULL)
				{
					mat[i][j] = -100000000;
				}
			}
		}


		int max = mat[0][0];
		int i_m = 0, j_m = 0;

		for(i = 0; i < this->i_size; i++)
		{
			for(j = 0; j < this->j_size; j++)
			{
				if (mat[i][j] > max)
				{
					max = mat[i][j];
					i_m = i;
					j_m = j;
				}
			}
		}
		
		this->matrix[i_m][j_m].val_ = type;
		Sleep(400 + rand()/100);
		return;
		
		
		for(i = 0; i < this->i_size; i++)
		{
			for(j = 0; j < this->j_size; j++)
			{
				cout << mat[i][j] << " ";
			}
			cout << endl;
		}
		_getch();
		//return;
	};

	bool board_rect::manual_move(int player_id)
	{
		int i, j;
		
		cout << "Enter row\n";
		cin >> i;
		cout << "Enter collumn\n";
		cin >> j;
		j--;
		i--;

		try
		{
			if ((i > this->i_size - 1) || (j > this->j_size - 1)|| cin.fail())
			{
				throw Index_Error();
			}
		}
		catch(Index_Error &IE)
		{
			IE.Error_Message();
			return false;
		}

		try
		{
			if (matrix[i][j].val_ != NULL)
			{
				throw Invalid_Move();
			}
		}
		catch(Invalid_Move &IM)
		{
			IM.Error_Message();
			return false;
		}

		matrix[i][j].val_ = (val) player_id;
		return true;
	};

	void board_rect::show()
	{
		int i, j, k;

		cout <<"\n";
		for (k = 0; k < j_size; k++)
		{
			cout <<  "________";
		}
		cout << "\n";

		for (i = 0; i < i_size; i++)
		{
			for (k = 0; k < j_size; k++)
			{
				cout <<  "|       ";
			}
			cout << "|\n";

			for (j = 0; j < j_size; j++)
			{
				cout << "| ";
				if (!((i / 9 != 0) || (j / 9 != 0)))
					cout << " ";
				this->matrix[i][j].show_s(i, j);
				cout << "  ";
			}
			cout <<"|\n";
				
			for (k = 0; k < j_size; k++)
			{
				cout <<  "|_______";
			}
			cout <<"|\n";
		}

	};
	
	//******************
	bool board_rect::check_row(int j)
	{
		int i;
		bool win = true;

		for(i = 0; i < this->i_size - 1; i++)
		{
			if (this->matrix[i][j].val_ == NULL)
			{
				return false;
			}
		}

		for(i = 0; i < this->i_size - 1; i++)
		{
			win = win && (this->matrix[i][j] == this->matrix[i + 1][j]);
		}

		if (win)
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	bool board_rect::check_column(int i)
	{
		int j;
		bool win = true;

		for(j = 0; j < this->j_size - 1; j++)
		{
		if (this->matrix[i][j].val_ == NULL)
			{
				return false;
			}
		}

		for(j = 0; j < this->j_size - 1; j++)
		{
			win = win && (this->matrix[i][j] == this->matrix[i][j + 1]);
		}
		if (win)
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	bool board_rect::check_vert_line(int j)
	{
		int counter = 0;

		for(int i = 0; i < this->i_size - 1; i++)
		{
			if ((this->matrix[i][j] == this->matrix[i + 1][j]) && (this->matrix[i][j].val_ != NULL))
			{
				counter++;
			}
			
			if (counter >= 4)
				return true;
		}
		return false;
	};

	bool board_rect::check_hor_line(int i)
	{
		int counter = 0;

		for(int j = 0; j < this->j_size - 1; j++)
		{
			if ((this->matrix[i][j] == this->matrix[i][j + 1]) && (this->matrix[i][j].val_ != NULL))
			{
				counter++;
			}

			if (counter >= 4)
				return true;
		}
		return false;
	};
	//******************

	bool board_rect::check_victory(int player_id)
	{
		for(int k = 0; k < this->i_size; k++)
		{
			if (this->check_column(k)  ||  this->check_hor_line(k))
			{
				if(player_id > 0)
				{
					system("cls");
					this->show();
					cout << "Player "  << player_id <<" won!\n";
					_getch();
				}
				return true;
			}
		}

		for(int l = 0; l < this->j_size; l++)
		{
			if (this->check_vert_line(l) || this->check_row(l))
			{
				if(player_id > 0)
				{
					system("cls");
					this->show();
					cout << "Player "  << player_id <<" won!\n";
					_getch();
				}
				return true;
			}
		}
		return false;
	};

	bool board_rect::check_draw()
	{
		int i, j;
		bool full = true;

		for (i = 0; i < i_size; i++)
		{
			for (j = 0; j < j_size; j++)
			{
				full = full && this->matrix[i][j].val_;
			}
		}
		full = full && !this->check_victory(-1);
		if (full)
		{
			system("cls");
			this->show();
			cout << "Game Draw\n";
			_getch();
		}
		return full;
	};