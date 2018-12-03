#include "board.h"

using namespace std;

class board_square: public board
{
private:
	int size;
	square** matrix;
	
	bool check_dia();
	int scan_row(int k, val type);
	int scan_collumn(int k, val type);
	int scan_dia_i(val type);
	int scan_dia_m(val type);
	bool check_row(int j);
	bool check_column(int i);
	bool check_hor_line(int j);
	bool check_vert_line(int i);

public:
	board_square(int S);
	~board_square();
	void cpu_move(int player_id, val type);
	bool manual_move(int player_id);
	void show();
	bool check_victory(int player_id);
	bool check_draw();
};

	board_square::board_square(int S)
	{
		int i, j;
		this->size = S;

		matrix = new square* [this->size];
		
		for (i = 0; i < size; i++)
		{
			for(j = 0; j < this->size; j++)
			{
				matrix[j] = new square [this->size];
			}
		}

		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
			{
				this->matrix[i][j].val_= NULL;
			}
		}
	};	

	board_square::~board_square()
	{
		delete this->matrix;
	};

	//------------------
	int board_square::scan_row(int k, val type)
	{
		int i, j, null_count = 0, type_count = 0, opon_count = 0;
		square **temp;

		temp = new square* [this->size];
		
		for (i = 0; i < size; i++)
		{
			for(j = 0; j < this->size; j++)
			{
				temp[j] = new square [this->size];
			}
		}

		temp = this->matrix;

		for (j = 0; j < this->size; j++)
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

	int board_square::scan_collumn(int k, val type)
	{
		int i, j, null_count = 0, type_count = 0, opon_count = 0;
		square **temp;

		temp = new square* [this->size];
		
		for (i = 0; i < size; i++)
		{
			for(j = 0; j < this->size; j++)
			{
				temp[j] = new square [this->size];
			}
		}

		temp = this->matrix;

		for (i = 0; i < this->size; i++)
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

	int board_square::scan_dia_i(val type)
	{
		int i, j, null_count = 0, type_count = 0, opon_count = 0;
		square **temp;
		temp = new square* [this->size];
		for (i = 0; i < size; i++)
		{
			for(j = 0; j < this->size; j++)
			{
				temp[j] = new square [this->size];
			}
		}
		
		temp = this->matrix;
		
		for (i = 0; i < this->size; i++)
		{
			if (temp[i][this->size - i]. val_ == NULL)
			{
				null_count++;
				opon_count -= 5;
			}
			if (temp[i][this->size - i]. val_ == type)
			{
				type_count++;
				opon_count = -1000;
			}
			if ((temp[i][this->size - i]. val_ != type) && (temp[i][size - i].val_ != NULL))
			{
				null_count = 0;
				type_count = 0;
				opon_count += 100;
			}
		}
		return(null_count + 4 * type_count + opon_count * 10);
	};

	int board_square::scan_dia_m(val type)
	{
		int i, j, null_count = 0, type_count = 0, opon_count = 0;
		square **temp;
		temp = new square* [this->size];
		for (i = 0; i < size; i++)
		{
			for(j = 0; j < this->size; j++)
			{
				temp[j] = new square [this->size];
			}
		}
		
		temp = this->matrix;
	
		for (i = 0; i < this->size; i++)
		{
			if (temp[i][i].val_ == NULL)
			{
				null_count++;
				opon_count = -100;
			}
			if (temp[i][i].val_ == type)
			{
				type_count++;
				opon_count = -1000;
			}
			if ((temp[i][i].val_ != type) && (temp[i][i].val_ != NULL))
			{
				null_count = 0;
				type_count = 0;
				opon_count += 100;
			}
		}
		return(null_count + type_count * 4 + opon_count * 10);
	};
	//------------------

	void board_square::cpu_move(int player_id, val type)
	{
		int **mat; 
		int i, j;
		
		square **temp;
		temp = new square* [this->size];
		for (i = 0; i < size; i++)
		{
			for(j = 0; j < this->size; j++)
			{
				temp[j] = new square [this->size];
			}
		}
		
		temp = this->matrix;
			
		mat = new int* [this->size];
		
		for (i = 0; i < size; i++)
		{
			for(j = 0; j < this->size; j++)
			{
				mat[j] = new int [this->size];
			}
		}
		
		for (i = 0; i < size; i++)
		{
			for(j = 0; j < this->size; j++)
			{
				mat[i][j] = 0;
			}
		}
		mat[size / 2][size / 2] = 10000;

		for (i = 0; i < this->size; i++)
		{
			for(j = 0; j < this->size; j++)
			{
				mat[i][j] += scan_row(i, type) + scan_collumn(j, type) + (rand() / 3);
			}
		}

		for (i = 0; i < this->size; i++)
		{
			mat[i][i] += scan_dia_m(type);
			mat[i][this->size - i] += scan_dia_i(type);
		}
		
		for(i = 0; i < this->size; i++)
		{
			for(j = 0; j < this->size; j++)
			{
				if (temp[i][j].val_ != NULL)
				{
					mat[i][j] = -100000000;
				}
			}
		}


		int max = mat[0][0];
		int i_m = 0, j_m = 0;

		for(i = 0; i < this->size; i++)
		{
			for(j = 0; j < this->size; j++)
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
		if (this->size < 9)
			Sleep(400 + rand()/100);
		return;
		
		
		for(i = 0; i < this->size; i++)
		{
			for(j = 0; j < this->size; j++)
			{
				cout << mat[i][j] << " ";
			}
			cout << endl;
		}
		getch();
		
	};

	bool board_square::manual_move(int player_id)
	{
		int f, i, j;
			
		cin >> f;
		f = f - 1;
		
		
		
			if ((f > this->size*size-1) || f < 0 || cin.fail())
			{
				throw Index_Error();
			}
		
		
		
		j = f % this->size ;
		i = f / this->size;

		if (matrix[i][j].val_ != NULL)
			{
				throw Invalid_Move();
			}



		matrix[i][j].val_ = (val) player_id;
		return true;
	};

	void board_square::show()
	{
		int i, j, k;

		cout <<"\n";
		for (k = 0; k < size; k++)
		{
			cout <<  "________";
		}
		cout << "\n";

		for (i = 0; i < size; i++)
		{
			for (k = 0; k < size; k++)
			{
				cout <<  "|       ";
			}
			cout << "|\n";

			for (j = 0; j < size; j++)
			{
				cout << "|  ";
				if ((j + i * size + 1) / 10 == 0)
					cout << " ";
				this->matrix[i][j].show_s(j + i * size);
				cout << "   ";
			}
			cout <<"|\n";
				
			for (k = 0; k < size; k++)
			{
				cout <<  "|_______";
			}
			cout <<"|\n";
		}
	};
	
	//******************
	bool board_square::check_row(int j)
	{
		int i;
		bool win = true;

		for(i = 0; i < this->size - 1; i++)
		{
			if (this->matrix[i][j].val_ == NULL)
			{
				return false;
			}
		}

		for(i = 0; i < this->size - 1; i++)
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

	bool board_square::check_column(int i)
	{
		int j;
		bool win = true;

		for(j = 0; j < this->size - 1; j++)
		{
		if (this->matrix[i][j].val_ == NULL)
			{
				return false;
			}
		}

		for(j = 0; j < this->size - 1; j++)
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

	bool board_square::check_dia()
	{
		int i, j;
		bool win_main = true, win_incidential = true;

		

		for (i = 0; i < size - 1; i++)
		{
			win_main = win_main && (this->matrix[i][i] == this->matrix[i + 1][i + 1]) && 
				(this->matrix[i + 1][i + 1].val_ != NULL) && (this->matrix[i][i].val_ != NULL);
		}

		for (i = 0; i < size - 1; i++)
		{
			j = size - i - 1;		
			win_incidential = win_incidential && (this->matrix[i][j] == this->matrix[i + 1][j - 1] && 
				(this->matrix[i][j].val_ != NULL) && (this->matrix[i + 1][j - 1].val_ != NULL));
			
		}
		return (win_main || win_incidential);
	};

	bool board_square::check_vert_line(int j)
	{
		int counter = 0;

		for(int i = 0; i < this->size - 1; i++)
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

	bool board_square::check_hor_line(int i)
	{
		int counter = 0;

		for(int j = 0; j < this->size - 1; j++)
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

	bool board_square::check_victory(int player_id)
	{
		int k;
		
		for(k = 0; k < this->size; k++)
		{
			if (this->check_row(k) || this->check_column(k) || this->check_hor_line(k) || this->check_vert_line(k))
			{
				if(player_id > 0)
				{
					system("cls");
					this->show();
					cout << "Player "  << player_id <<" won!\n";
					getch();
				}
				return true;
			}
		}

		if (this->check_dia())
		{
			if(player_id > 0)
			{
				system("cls");
				this->show();
				cout << "Player "  << player_id <<" won!\n";
				getch();
			}
			return true;
		}

		return false;
	};

	bool board_square::check_draw()
	{
		int i, j;
		bool full = true;

		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
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
			getch();
		}
		return full;
	};