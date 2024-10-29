#pragma once
#include <vector>
#include"Card.h"
class Board 
{
private :
	int size;
	
	std::vector < std::vector < Card >> board= {};
	std::vector<std::vector<bool>> marked ;

public:

	void updateMarked(int col, int row );
	bool verifyEmpty(int row , int col);
	void display();
	bool makeMove(int col , int row , Card card );
	bool CheckWinner(Card card);
	bool isDraw();
	void resetBoard();
};
