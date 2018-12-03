#ifndef BOARD_ERROR

#define BOARD_ERROR
#include <ostream>
#include <conio.h>

#define DEBUG

class Board_Error 
{
public:
	Board_Error() {};

	virtual void Error_Message() 
	{
		std::cerr << "An Error has occurred\n";
	}

	void Continue() const 
	{
#ifdef DEBUG
		std::cerr << "The program will be continued...\n";
		_getch();
#else
		throw;
#endif
	}
};

class Invalid_Move : public Board_Error 
{
private:

public:
	Invalid_Move(){};

	void Error_Message() const 
	{
		std::cerr << "Invalid Move!\n";
		Continue();
	}
};

class Index_Error : public Board_Error 
{
private:

public:
	Index_Error(){};

	void Error_Message() const 
	{
		std::cerr << "Index exceeded\n";
		Continue();
	}
};

#endif