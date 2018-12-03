#undef identifier
#include <string>
using namespace std;

enum identifier
{
	Human,
	CPU
};

class player
{
public:
	identifier type;
	int id;
	val fig;

	player(int I, identifier T, val F)
	{
		this->id = I;
		this->type = T;
		this->fig = F;
	}

	void info()
	{
		cout << "Player " << this->id;
		switch(this->fig)
		{
			case X:
			{
				cout << " - X";
				break;
			}
			case O:
			{
				cout << " - O";
				break;
			}
		}

		switch(this->type)
		{
			case Human:
			{
				cout << " - Human";
				break;
			}
			case CPU:
			{
				cout << " - CPU";
				break;
			}
		}
		cout << endl;
	}
};

	bool operator <(player &left, player &right)
	{
		if(left.id < right.id)
			return true;
		else 
			return false;
	}