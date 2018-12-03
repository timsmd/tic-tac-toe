#include <windows.h>
#include "square.h"
#include "Board_Error.h"

class board
{
protected:
	int size;
	int i_size, j_size;
public:
	board(){};
	board(int, int) {};
	board(int){};
	virtual void cpu_move(int player_id, val type) = 0;
	virtual bool manual_move(int player_id) = 0;
	virtual void show() = 0;
	virtual bool check_victory(int player_id) = 0;
	virtual bool check_draw() = 0;
};